#include <iostream>
#include "Hadamard.hpp"
#include "QMem.hpp"

#include <boost/compute/command_queue.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout << "Not enough cmd line args\n";
        return -1;
    }
    srand(time(NULL));
    compute::device device = compute::system::default_device();
    compute::context context(device);
    compute::command_queue queue(context, device);
    
    int bits = std::stoi(argv[1]);
    Hadamard hadamard(context);
    QMem qmem(bits, queue);
    for (int i = 0; i < bits; i++) {
        qmem.apply(hadamard, i);
    }
    std::cout << qmem.measure() << "\n";
    return 0;
}