#include "omp.h"
#include "src/QMem.hpp"
#include "src/unarygates/Hadamard.hpp"
#include "src/unarygates/PauliX.hpp"
#include "src/unarygates/PauliZ.hpp"
#include "src/gates/Control.hpp"
#include "src/gates/Gate.hpp"
#include <vector>
#include <complex>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

void oracle(QMem& qmem, int randNum, int qubits, int reg) {
    std::vector<int> controlBits;
    std::vector<int> notControlBits;
    for (int i = 0; i < qubits; i++) {
        if ((randNum >> i) & 1) {
            controlBits.push_back(reg + qubits - i - 1);
        } else {
            notControlBits.push_back(reg + qubits - i - 1);
        }
    }
    PauliX pauliX;
    ControlGate gate(pauliX, controlBits, notControlBits, reg + qubits);
    qmem.apply(gate);
}

void diffusion(QMem& qmem, std::vector<int> bits, int index) {
    std::vector<int> empty(0);
    PauliZ pauliZ;
    ControlGate gate(pauliZ, empty, bits, index);
    PauliX gate2;
    
    qmem.apply(gate2, index);
    
    qmem.apply(gate);
    qmem.apply(gate2, index);
}

bool correct(QMem& qmem, int qubits, int guess, int randNum) {
    if (guess == -1) {
        return false;
    }
    PauliX pauliX;
    int reg = qmem.alloc(qubits + 1);
    if (reg == -1) {
        throw -1;
    }
    for (int i = 0; i < qubits; i++) {
        if ((guess >> i) & 1) {
            qmem.apply(pauliX, reg + qubits - i - 1);
        }
    }
    oracle(qmem, randNum, qubits, reg);
    auto measureVal = qmem.measure(reg + qubits);
    qmem.free(reg, qubits + 1);
    return measureVal == 1;
}

int main(int argc, char const *argv[])
{   
    srand(time(NULL));

    if (argc != 2) {
        return -1;
    }
    
    int qubits = std::stoi(argv[1]);
    int guess = -1;
    int totalOptions = (int)pow(2, qubits);
    int randNum = rand() % totalOptions;

    QMem qmem(2*(qubits+1));
    
    int reg = qmem.alloc(qubits + 1);
    std::vector<int> bits;
    for (int x = 0; x < qubits; x++) {
        bits.push_back(reg + x);
    }
    Hadamard hadamard;
    PauliX pauliX;

    std::vector<int> aBits;
    for (int x = 0; x < qubits - 1; x++) {
        aBits.push_back(reg + x);
    }
    double iterations = pow(2, qubits/2);
    if (double(int(iterations)) != iterations) {
        iterations ++;
    }
    int intIterations = (int)iterations;

    while (!correct(qmem, qubits, guess, randNum)) {
        
 
        
        qmem.apply(pauliX, reg + qubits);
        qmem.apply(hadamard, bits);
        qmem.apply(hadamard, reg+qubits);
        for (int i = 0; i < iterations - 1; i++) {
            oracle(qmem, randNum, qubits, reg);
       
            qmem.apply(hadamard, bits);
            diffusion(qmem, aBits, reg + qubits - 1);
            qmem.apply(hadamard, bits);
        }


    
        
        guess = qmem.measure(reg, qubits);

        std::cout << randNum << "\n";
        std::cout << guess << "\n";
    }
    
    return 0;
}
