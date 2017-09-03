#include <ctime>
#include <iostream>
#include "omp.h"
#include <boost/compute/command_queue.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

 const char source[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
     kernel void square(                                   //   2
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
        // output[i] = (input[i] + input[j]);
        // output[i] = c * (input[i] + input[j]);
        // output[i] *= c;
    }
    // } else {
        // int j = i ^ z;
        // output[i] *= c;
        // output[i] = c * (input[i] - input[j]);
    // }
    // output[i] = input[i] * input[i];
}
 );

#include <vector>
using namespace std;

int main()
{
    // get the default device
    int bits = 18;
    float c = 1.0 / sqrt(2);

    compute::device device = compute::system::default_device();
    compute::context context(device);
    compute::command_queue queue(context, device);
    compute::program square_program = compute::program::build_with_source(source, context);
    compute::kernel kernel(square_program, "square");

    std::vector<float> int_data(pow(2,bits),0);
    int_data[0] = 1;
    compute::vector<float> values(int_data.begin(),int_data.end(), queue);
    

    kernel.set_arg(0, values);
    
    kernel.set_arg(2, c);

    for (int index = 0; index < bits; index++ ){
        int z = 1 << index;
    
        kernel.set_arg(1, index);
        kernel.set_arg(3, z);
        queue.enqueue_1d_range_kernel(kernel, 0, values.size(),0);

    }

    // std::cout << "int's: ";
    // compute::copy(
    //     values.begin(), values.end(),
    //             std::ostream_iterator<float>(std::cout, " "),
    //     queue
    // );
    // std::cout << std::endl;

    // std::vector<float> reg(pow(2,bits),0);
    // reg[0] = 1;
    // for (int index = 0; index < bits; index++ ){
    //     int z = 1 << index;

    //     #pragma omp parallel for
    //     for (unsigned int i = 0; i < reg.size(); i++) {

    //     // for (unsigned int m = 0; m < reg.size(); m += (int)pow(2,index)) {
    //         // #pragma omp parallel for
    //         // for (unsigned int i = m; i < m + pow(2, index - 1); i++) {
    //         // for (unsigned int n = 0; n < pow(2, index - 1); n++) {
    //             // unsigned int i = m + n;
    //         if (!(i >> index & 1)) {
    //             unsigned int j = i ^ z;
    //             float tmp = reg[i];
    //             reg[i] = c * (reg[j] + reg[i]);
    //             reg[j] = c * (tmp - reg[j]);
    //         }
    //     // }
    //     }
    // }

    return 0;
}

// std::cout << "int's: ";
    // compute::copy(
    //     values.begin(), values.end(),
    //     std::ostream_iterator<int>(std::cout, " "),
    //     queue
    // );
    // std::cout << std::endl;

