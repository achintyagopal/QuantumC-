#include <vector>
#include <complex>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

#include "QMem.hpp"
#include "PauliX.hpp"
#include "Hadamard.hpp"
#include "PauliZ.hpp"
#include "Control.hpp"

#include <boost/compute/command_queue.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/container/vector.hpp>

void oracle(QMem& qmem, int randNum, int qubits, compute::context& context) {
    std::vector<int> controlBits;
    std::vector<int> notControlBits;
    for (int i = 0; i < qubits; i++) {
        if (randNum >> i & 1) {
            controlBits.push_back(qubits - i - 1);
        } else {
            notControlBits.push_back(qubits -i - 1);
        }
    }
    PauliX pauliX(context);
    Control gate(pauliX, controlBits, notControlBits, qubits, context);
    qmem.apply(gate);
}

void diffusion(QMem& qmem, std::vector<int> bits, int index, compute::context& context) {
    std::vector<int> empty(0);
    PauliZ pauliZ(context);
    Control gate(pauliZ, empty, bits, index, context);
    PauliX pauliX(context);

    qmem.apply(pauliX, index);
    qmem.apply(gate);
    qmem.apply(pauliX, index);
}

bool correct(int qubits, int guess, int randNum, compute::command_queue& queue, compute::context& context) {
    if (guess == -1) {
        return false;
    }

    PauliX pauliX(context);
    QMem qmem(qubits + 1, queue);

    for (int i = 0; i < qubits; i++) {
        if (guess >> i & 1) {
            qmem.apply(pauliX, qubits - i -1);
        }
    }
    oracle(qmem, randNum, qubits, context);
    int measureVal = qmem.measure();
    return true;
    // return measureVal & 1;
}

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
    int guess = -1;
    int totalOptions = (int)pow(2, qubits);
    int randNum = rand() % totalOptions;

    
    std::vector<int> bits;
    for (int x = 0; x < qubits; x++) {
        bits.push_back(x);
    }

    Hadamard hadamard(context);
    PauliX pauliX(context);

    std::vector<int> aBits;
    for (int x = 0; x < qubits - 1; x++) {
        aBits.push_back(x);
    }

    double floatIterations = pow(2, qubits/2);
    if (double(int(floatIterations)) != floatIterations) {
        floatIterations ++;
    }
    int iterations = (int)floatIterations;
    std::cout << randNum << "\n";
    
    while (!correct(qubits, guess, randNum, queue, context)) {

        QMem qmem(qubits + 1, queue);
        qmem.apply(pauliX, qubits);
        qmem.apply(hadamard, bits);
        qmem.apply(hadamard, qubits);
        for (int i = 0; i < iterations - 1; i++) {
            oracle(qmem, randNum, qubits, context);

            qmem.apply(hadamard, bits);
            diffusion(qmem, aBits, qubits - 1, context);
            qmem.apply(hadamard, bits);
        }

        guess = qmem.measure() >> 1;
        std::cout << guess << "\n";
    }

    return 0;
}