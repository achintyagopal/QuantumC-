#include <cmath>
#include <utility>
#include "QMem.hpp"
#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>

QMem::QMem(int qubits):entanglements(qubits) {

    srand(time(NULL));
    totalBits = qubits;
    freeChunks.push_back(std::pair<int,int>(0, qubits));

}

int QMem::alloc(int len) {

    for (auto it = freeChunks.begin() ; it != freeChunks.end(); ++it) {

        auto& currPair = *it;
        int length = std::get<1>(currPair);
        if (length >= len) {
            int idx = std::get<0>(currPair);
            if (length == len) {
                freeChunks.erase(it);
            } else {
               std::get<1>(currPair) = length - len;
               std::get<0>(currPair) += len;
            }

            for (int i = 0; i < len; i++) {
                std::shared_ptr<std::vector<std::complex<double> > > reg(
                    new std::vector<std::complex<double> >(2));
                (*reg)[0] += 1;
                allocBits[idx + i] = std::pair<std::shared_ptr<std::vector<
                std::complex<double> > >, int>(reg,0);
            }
            return idx;
        }
    }

    return -1;
}

void QMem::free(int idx, int len) {
    this->measure(idx, len);
    for (int i = idx; i < idx + len; i++) {
        allocBits.erase(i);
    }
    freeChunks.push_back(std::pair<int,int>(idx,len));
}

long QMem::measure(int idx, int len) {
    if (len > 64) {
        // throw error
    }

    long measurement = 0;
    for (int i = idx; i< idx + len; i++) {
        measurement <<= 1;
        measurement += measure(i);   
    }
    return measurement;
}

int QMem::measure(int idx) {
    
    auto& regIdx = allocBits.at(idx);
    auto& reg = std::get<0>(regIdx);
    auto index = std::get<1>(regIdx);
    // measure index in reg
    int randomVal = rand();
    // double r = ((double) (randomVal)/ (RAND_MAX));
    double r = ((double) (randomVal % 100000)/ (100001));

    int i = 0;
    while (r > 0) {
        r -= std::norm((*reg)[i]);
        i++;
    }
    i--;

    int measurement = (i >> index) & 1;

    double totalSum = 0;
    for (i = 0; i < reg->size(); i++) {
        // sum up over measurement
        if (measurement == ((i >> index) & 1)) {
           totalSum += std::norm((*reg)[i]);
        }
    }

    int newSize = reg->size() / 2;
    std::shared_ptr<std::vector<std::complex <double > > > newResult(
        new std::vector<std::complex <double > >(newSize));

    for (i = 0; i < reg->size(); i++) {
        // sum up over measurement
        if (measurement == ((i >> index) & 1)) {

            int j = ((i >> (index + 1)) << (index )) + (i & ((1 << index) - 1));
            (*newResult)[j] = (*reg)[i] / std::sqrt(totalSum);
        }
    }
    // create shared ptr of vector of complex of double
    // iterate through, if measurement, remove measurement, num/sum

    std::vector<int> idxs = entanglements.find(idx);
    for (int i = 0; i < idxs.size(); i++) {

        int childIdx = idxs[i];
        if (idx == childIdx) {
            std::shared_ptr<std::vector<std::complex<double> > > measureReg(new std::vector<std::complex<double> >(2));
            (*measureReg)[measurement] += 1;
            std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> newPair(measureReg, 0);
            allocBits.erase(childIdx);
            allocBits[childIdx] = newPair;
            continue;
        }
        int regIdx = std::get<1>(allocBits.at(childIdx));

        if (regIdx > index) {
            std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> newPair(newResult, regIdx - 1);
            allocBits.erase(childIdx);
            allocBits[childIdx] = newPair;
        } else {
            std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> newPair(newResult, regIdx);
            allocBits.erase(childIdx);
            allocBits[childIdx] = newPair;

        }
    }

    entanglements.detach(idx);
    
    return measurement;
}

void QMem::combine(int index, int length) {
    
    std::set<uintptr_t> addresses;
    std::shared_ptr<std::vector<std::complex<double> > > completeReg(
        new std::vector<std::complex<double> >(1));
    (*completeReg)[0] += 1;
    std::map<int,int> newIdxs;
    int bits = 0;
    for (int i = index; i < index + length; i++) {
        auto& inputPair = allocBits.at(i);
        auto& reg = std::get<0>(inputPair);
        auto index = std::get<1>(inputPair);

        if (std::get<1>(addresses.insert((uintptr_t)&reg))) {
            std::vector<int> idxs = entanglements.find(i);
            if (i != index) {
                entanglements.append(i, index);
            }

            // multiply reg (outer loop) with completeReg
            std::shared_ptr<std::vector<std::complex<double> > > completeRegTmp(
                new std::vector<std::complex<double> >());

            for (int k = 0; k < reg->size(); k++) {
                for (int j = 0; j < completeReg->size(); j++) {
                    completeRegTmp->push_back((*reg)[k] * (*completeReg)[j]);
                }
            }
            completeReg = completeRegTmp;

            for (int j = 0; j < idxs.size(); j++) {
                int idx = idxs[j];
                newIdxs[idx] = std::get<1>(allocBits.at(idx)) + bits;
            }
            bits += idxs.size();
        }
    }

    for (auto it = newIdxs.begin(); it != newIdxs.end(); ++it) {
        allocBits.erase(it->first);
        allocBits[it->first] = std::pair<std::shared_ptr<std::vector<
        std::complex<double> > >, int>(completeReg,it->second);
    }

}

void QMem::apply(Gate& gate) {
    gate.apply(allocBits, entanglements);
    // this->combine(index, gate.size());
    // std::map<int, int> indexMap;
    // for (unsigned int i = 0; i < gate.size(); i++) {
        // indexMap[i] = std::get<1>(allocBits.at(index + i));
    // }
    // gate.apply(std::get<0>(allocBits.at(index)), indexMap);
}

void QMem::apply(UnaryGate& gate, std::vector<int>& idxs) {
    for (auto it = idxs.begin() ; it != idxs.end(); ++it) {
        gate.apply(allocBits.at(*it));
    }

}

void QMem::apply(UnaryGate& gate, int index) {
    gate.apply(allocBits.at(index));

}
