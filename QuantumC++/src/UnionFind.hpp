#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <utility>
#include <vector>

class UnionFind {
public:
    std::vector<std::pair<int, std::vector<int> > > v;

    int findRoot(int a);
    std::vector<int> findHelper(int a);

    UnionFind(int size);
    void append(int a, int b);
    std::vector<int> find(int a);
    void detach(int a);

};

#endif