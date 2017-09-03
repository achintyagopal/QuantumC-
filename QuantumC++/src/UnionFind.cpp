#include "UnionFind.hpp"
#include <iostream>
#include <algorithm>

UnionFind::UnionFind(int size) {
    for (int i = 0; i < size; i++) {
        std::pair<int, std::vector<int> > parChild;
        std::get<0>(parChild) = -1;
        v.push_back(parChild);
    }
}

void UnionFind::append(int a, int b) {
    int rootA = this->findRoot(a);
    int rootB = this->findRoot(b);
    if (rootA != rootB) {
        std::get<0>(v[rootA]) = rootB;
        auto a = std::get<1>(v[rootB]);
        std::get<1>(v[rootB]).push_back(rootA);
    }  
}

std::vector<int> UnionFind::find(int a) {
    int parent = this->findRoot(a);
    auto result = this->findHelper(parent);
    result.push_back(parent);
    return result;

}

std::vector<int> UnionFind::findHelper(int a) {
    std::vector<int> allChildren;
    std::vector<int> children = std::get<1>(v[a]);
    for (auto it = children.begin(); it != children.end(); it++) {
        std::vector<int> results = this->findHelper(*it);
        for (auto it2 = results.begin(); it2 != results.end(); it2++) {
            allChildren.push_back(*it2);
        }
        allChildren.push_back(*it);
    }
    return allChildren;
}

int UnionFind::findRoot(int a) {
    int parent = std::get<0>(v[a]);
    if (parent == -1) {
        return a;
    } 
    int root = this->findRoot(parent);
    return root;
}

void UnionFind::detach(int a) {
    auto parent = std::get<0>(v[a]);
    auto children  = std::get<1>(v[a]);
    if (parent == -1) {
        if (children.size() != 0) {
            std::get<0>(v[children[0]]) = -1;
            for (int i = 1; i < children.size(); i++) {
                std::get<1>(v[children[0]]).push_back(children[1]);
                std::get<0>(v[children[1]]) = children[0];
            }
        }
    } else {
        
        auto it = children.begin();
        while (it != children.end()) {
            std::get<0>(v[*it]) = parent;
            std::get<1>(v[parent]).push_back(*it);
            it++;
        }
        auto& parentChild = std::get<1>(v[parent]);
        parentChild.erase(std::remove(parentChild.begin(), parentChild.end(), a), parentChild.end());
    }

    std::pair<int, std::vector<int> > parChild;
    std::get<0>(parChild) = -1;
    v[a] = parChild;
}