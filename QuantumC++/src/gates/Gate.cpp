#include "Gate.hpp"

void Gate::combine(std::vector<int>& combBits,std::map<int, std::pair<std::shared_ptr<std::vector<std::complex<double> > >, int> >& allocBits, UnionFind& entanglements) {
    
    std::set<uintptr_t> addresses;
    std::shared_ptr<std::vector<std::complex<double> > > completeReg(
        new std::vector<std::complex<double> >(1));
    (*completeReg)[0] += 1;
    std::map<int,int> newIdxs;
    int bits = 0;
 

    for (int m = 0; m < combBits.size();m++) {
        int i = combBits[m];

        auto& inputPair = allocBits.at(i);

        auto& reg = std::get<0>(inputPair);
        auto index = std::get<1>(inputPair);
        if (std::get<1>(addresses.insert((uintptr_t)&(*reg)))) {
            // if (m != 0) {
                // entanglements.append(i, combBits[0]);
            // }
            std::vector<int> idxs = entanglements.find(i);


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
    for (int m = 1; m < combBits.size();m++) {
        entanglements.append(combBits[0], combBits[m]);
    }
    // if (addresses.size() != 1) {
    for (auto it = newIdxs.begin(); it != newIdxs.end(); ++it) {
        allocBits.erase(it->first);
        allocBits[it->first] = std::pair<std::shared_ptr<std::vector<
            std::complex<double> > >, int>(completeReg,it->second);
    }

  
// }
}