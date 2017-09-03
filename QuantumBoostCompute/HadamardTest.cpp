#include <vector>
#include "Hadamard.hpp"
#include "QMem.hpp"

#include <boost/compute/command_queue.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

int main(int argc, char const *argv[])
{
    compute::device device = compute::system::default_device();
    compute::context context(device);
    compute::command_queue queue(context, device);
    
    int bits = 22;
    // compute::vector<double> reg(4,0.,queue);
    Hadamard hadamard(context);
    QMem qmem(bits, queue);
    for (int i = 0; i < bits; i++) {
        qmem.apply(hadamard, i);
    }
    return 0;
}