#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <complex>
#include <vector>
#include <utility>
#include <memory>
#include "Gate.hpp"
#include "../unarygates/UnaryGate.hpp"

class ControlGate : public Gate {
    UnaryGate& gate;
    std::vector<int> controlBits;
    std::vector<int> notControlBits;
    int index;
public:
    ControlGate(UnaryGate& gate_, std::vector<int>& controlBits, std::vector<int>& notControlBits, int index) :gate(gate_){
        this->controlBits = controlBits;
        this->notControlBits = notControlBits;
        this->index = index;
    };
    // ControlGate(std::vector<int>& controlBits, std::vector<int>& notControlBits, int index){
        // this->controlBits = controlBits;
        // this->notControlBits = notControlBits;
        // this->index = index;
    // };
    virtual void apply( std::map<int, std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> >& allocBits, UnionFind& entanglements);
};

#endif