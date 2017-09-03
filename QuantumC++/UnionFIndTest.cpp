#include "src/UnionFind.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    UnionFind find(10);
    find.append(0,1);
    auto a = find.find(0);
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << "\n";
    }

    return 0;
}