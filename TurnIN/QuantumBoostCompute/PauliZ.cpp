#include "PauliZ.hpp"
#include <cmath>

namespace compute = boost::compute;

PauliZ::PauliZ(compute::context& context) {
     const char source[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
        kernel void pauliz(                                   //   2
                    global float* input,             //   3
                    int index)
        {
            size_t i = get_global_id(0);

            if ( (i >> index & 1)) {
                input[i] *= -1;
            }
        }
    );

    compute::program program = compute::program::build_with_source(source, context);
    compute::kernel _kernel(program, "pauliz");
    kernel = _kernel;
}

void PauliZ::apply(compute::vector<float>& reg, int index, compute::command_queue& queue) {


    int z = 1 << index;
    kernel.set_arg(0, reg);
    kernel.set_arg(1, index);
    queue.enqueue_1d_range_kernel(kernel, 0, reg.size(),0);
    // for (int i = 0; i < reg.size(); i++) {
    //     if (i >> index & 1) {
    //         reg[i] *= -1;
    //     }
    // }
}  