#ifndef QMEM_HPP
#define QMEM_HPP

#include <vector>
#include <complex>
#include <map>
#include <utility>
#include <memory>

#include "gates/Gate.hpp"
#include "unarygates/UnaryGate.hpp"
#include "UnionFind.hpp"

class QMem {
public:
    int totalBits;
    std::map<int, std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> > allocBits;
    std::vector< std::pair<int, int> > freeChunks;
    UnionFind entanglements;

    void combine(int index, int length);

    QMem(int qubits);
    int alloc(int len);
    void free(int idx, int len);
    long measure(int idx, int len);
    int measure(int idx);
    void apply(Gate& gate);
    void apply(UnaryGate& gate, std::vector<int>& idxs);
    void apply(UnaryGate& gate, int index);
};

#endif