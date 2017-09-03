#include "omp.h"
#include "Control.hpp"

Control::Control(UnaryGate& gate_, std::vector<int>& controlBits, std::vector<int>& notControlBits, int index) :gate(gate_) {
    this->controlBits = controlBits;
    this->notControlBits = notControlBits;
    this->index = index;
}

void Control::apply(std::vector<double>& reg) {

    std::vector<double> result(reg.size());

    #pragma omp parallel for
    for (int y = 0; y < reg.size(); y++) {
        bool control = true;
        for (int i = 0; i < controlBits.size(); i++) {
            int index = controlBits[i];
            if (!((y >> index) & 1)) {
                control = false;
                break;
            }
        }
        if (control) {
            for (int i = 0; i < notControlBits.size(); i++) {
                int index = notControlBits[i];
                if ((y >> index) & 1) {
                    control = false;
                    break;
                }
            }
        }
        if (control) {
            result[y] = reg[y];
            reg[y] = 0;
        }
    }

    gate.apply(result, index);

    #pragma omp parallel for
    for (int y = 0; y < reg.size(); y++) {
        reg[y] += result[y];
    }

}
