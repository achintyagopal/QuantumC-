#include <iostream>
#include "Hadamard.hpp"
#include <cmath>

namespace compute = boost::compute;

Hadamard::Hadamard(compute::context& context) {
    constant = 1./sqrt(2);

     const char source[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
     kernel void hadamard(                                   //   2
                   global float* input,             //   3
                    int index,
                    float c,
                    int z)
{
    size_t i = get_global_id(0);

    if ( !(i >> index & 1)) {
        int j = i ^ z;
        float tmp = input[i];
        input[i] = c * (input[j] + input[i]);
        input[j] = c * (tmp - input[j]);
    }
});

    compute::program program = compute::program::build_with_source(source, context);
    compute::kernel _kernel(program, "hadamard");
    kernel = _kernel;
}

void Hadamard::apply(compute::vector<float>& reg, int index, compute::command_queue& queue) {

    int z = 1 << index;
    kernel.set_arg(0, reg);
    kernel.set_arg(1, index);
    kernel.set_arg(2, constant);
    kernel.set_arg(3, z);
    queue.enqueue_1d_range_kernel(kernel, 0, reg.size(),0);

}  
