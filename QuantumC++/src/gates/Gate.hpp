#ifndef GATE_HPP
#define GATE_HPP

#include <complex>
#include <vector>
#include <map>
#include <memory>
#include <set>
#include <iostream>
#include "../UnionFind.hpp"

class Gate {

public:
    virtual void apply( std::map<int, std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> >& allocBits, UnionFind& entanglements) = 0;
protected:
    void combine(std::vector<int>& combBits,std::map<int, std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> >& allocBits, UnionFind& entanglements);

}
;

#endif