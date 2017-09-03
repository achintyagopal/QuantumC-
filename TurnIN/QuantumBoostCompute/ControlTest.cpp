#include <vector>
#include <complex>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

#include "QMem.hpp"
#include "PauliX.hpp"
#include "Control.hpp"
#include "Hadamard.hpp"

#include <boost/compute/command_queue.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    if (argc != 2) {
        std::cout << "Not enough cmd line args\n";
        return -1;
    }

    compute::device device = compute::system::default_device();
    compute::context context(device);
    compute::command_queue queue(context, device);
    
    int qubits = std::stoi(argv[1]);

    Hadamard hadamard(context);
    PauliX pauliX(context);

    std::vector<int> aBits;
    for (int x = 0; x < 1; x++) {
        aBits.push_back(x);
    }

    QMem qmem(qubits, queue);
    qmem.apply(pauliX, 0);
    // for (int i = 0; i < qubits; i++) {
    //     qmem.apply(hadamard, i);
    // }

    

    // std::vector<int> empty;

    // Control gate(pauliX, aBits, empty, qubits - 1, context);
    // qmem.apply(gate);

    qmem.measure();

    return 0;
}
