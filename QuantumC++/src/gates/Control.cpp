#include "Control.hpp"

void ControlGate::apply( std::map<int, std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> >& allocBits, UnionFind& entanglements) {
    this->combine(controlBits, allocBits, entanglements);
    this->combine(notControlBits, allocBits, entanglements);
    std::vector<int> combineBits;
    if (controlBits.size() != 0) {
        combineBits.push_back(controlBits[0]);
        
    }
    if (notControlBits.size() != 0) {
        combineBits.push_back(notControlBits[0]);
        
    }

    combineBits.push_back(index);
    this->combine(combineBits, allocBits, entanglements);

   
    auto& reg = std::get<0>(allocBits.at(index));
    std::shared_ptr<std::vector<std::complex<double> > > result(new std::vector<std::complex<double> >(reg->size()));
    for (int y = 0; y < reg->size(); y++) {
        bool control = true;
        for (int i = 0; i < controlBits.size(); i++) {
            int x = controlBits[i];
            
            int index = std::get<1>(allocBits[x]);
            if (!((y >> index) & 1)) {
                control = false;
                break;
            }
        }
        if (control) {
            for (int i = 0; i < notControlBits.size(); i++) {
                int x = notControlBits[i];
                
                int index = std::get<1>(allocBits[x]);
                if ((y >> index) & 1) {
                    control = false;
                    break;
                }
            }
        }
        if (control) {
            (*result)[y] = (*reg)[y];
        }
    }
    std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> unaryPair(result, std::get<1>(allocBits.at(index)));
    gate.apply(unaryPair);

    for (int y = 0; y < reg->size(); y++) {
        bool control = true;
        for (int i = 0; i < controlBits.size(); i++) {
            int x = controlBits[i];
            int index = std::get<1>(allocBits[x]);
            if (!((y >> index) & 1)) {
                control = false;
                break;
            }
        }
        if (control) {
            for (int i = 0; i < notControlBits.size(); i++) {
                int x = notControlBits[i];
                int index = std::get<1>(allocBits[x]);
                if ((y >> index) & 1) {
                    control = false;
                    break;
                }
            }
        }
        if (!control) {
            (*result)[y] += (*reg)[y];
        }
    }

    (*reg) = (*result);
    

}