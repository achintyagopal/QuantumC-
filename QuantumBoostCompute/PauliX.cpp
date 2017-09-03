#include "PauliX.hpp"
#include <cmath>

namespace compute = boost::compute;

PauliX::PauliX(compute::context& context) {
    const char source[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
        kernel void paulix(                                   //   2
                    global float* input,             //   3
                    int index,
                    int z)
        {
            size_t i = get_global_id(0);

            if (!(i >> index & 1)) {
                int j = i ^ z;
                float tmp = input[i];
                input[i] = input[j];
                input[j] = tmp;
            }
        }
    );

    compute::program program = compute::program::build_with_source(source, context);
    compute::kernel _kernel(program, "paulix");
    kernel = _kernel;
}

void PauliX::apply(compute::vector<float>& reg, int index, compute::command_queue& queue) {

    int z = 1 << index;
    kernel.set_arg(0, reg);
    kernel.set_arg(1, index);
    kernel.set_arg(2, z);
    queue.enqueue_1d_range_kernel(kernel, 0, reg.size(),0);
}
