#include <iostream>
#include "Control.hpp"

namespace compute = boost::compute;

Control::Control(UnaryGate& gate_, std::vector<int>& controlBits, std::vector<int>& notControlBits, int index,
    compute::context& context) :gate(gate_) {

    this->controlBits = controlBits;
    this->notControlBits = notControlBits;
    this->index = index;

    const char source[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
     kernel void controlFn(                                   //   2
                   global float* input,
                   global float* output,             //   3
                    global int* controlBits,
                    int n,
                    global int* notControlBits,
                    int m)
{
    size_t y = get_global_id(0);

    bool control = true;
    for (int i = 0; i < n; i++) {
        int index = controlBits[i];
        if (!(y >> index & 1)) {
            control = false;
            break;
        }
    }
    if (control){
        for (int i = 0; i < m; i++) {
            int index = notControlBits[i];
            if (y >> index & 1) {
                control = false;
                break;
            }
        }   
    }
    if (control) {
        output[y] = input[y];
        input[y] = 0;
    }

}
 );

    compute::program program = compute::program::build_with_source(source, context);
    compute::kernel _kernel(program, "controlFn");
    kernel = _kernel;

    const char source2[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
     kernel void controlFn2(                                   //   2
                   global float* input,
                   global float* output)
{
    size_t y = get_global_id(0);

    input[y] += output[y];

}
 );

    compute::program program2 = compute::program::build_with_source(source2, context);
    compute::kernel _kernel2(program2, "controlFn2");
    kernel2 = _kernel2;
}

void Control::apply(compute::vector<float>& reg, compute::command_queue& queue){

    compute::vector<int> controlBitsCL(controlBits.begin(), controlBits.end(), queue);
    compute::vector<int> notControlBitsCL(notControlBits.begin(), notControlBits.end(), queue);
    compute::vector<float> result(reg.size(), 0., queue);

    kernel.set_arg(0, reg);
    kernel.set_arg(1, result);
    kernel.set_arg(2, controlBitsCL);
    kernel.set_arg(3, (int)controlBits.size());
    kernel.set_arg(4, notControlBitsCL);
    kernel.set_arg(5, (int)notControlBits.size());
    queue.enqueue_1d_range_kernel(kernel, 0, reg.size(),0);

    controlBitsCL.clear();
    notControlBitsCL.clear();

    gate.apply(result, index, queue);
 

    kernel2.set_arg(0, reg);
    kernel2.set_arg(1, result);
    queue.enqueue_1d_range_kernel(kernel2, 0, reg.size(),0);

}
