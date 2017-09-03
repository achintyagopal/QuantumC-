#include <utility>
#include <iostream>
#include <map>
#include <vector>
#include <memory>

void fn (std::map<int, std::shared_ptr<std::vector<int> > >& mapTest) {
    std::shared_ptr<std::vector<int> > v = std::make_shared<std::vector<int> >();
    v->push_back(2);
    v->push_back(1);
    mapTest[0] = v;
    mapTest[1] = v;
    std::cout << v.use_count() << "\n";
    std::cout << mapTest[0].use_count() << "\n";
}


void gn (std::map<int, std::vector<int>* > mapTest) {
    std::vector<int>* v = new std::vector<int>();
    v->push_back(2);
    v->push_back(1);
    mapTest[0] = v;
    mapTest[1] = v;
    // std::cout << v.use_count() << "\n";
    // std::cout << mapTest[0].use_count() << "\n";
}

int main(int argc, char const *argv[])
{
    // std::map<int, std::shared_ptr<std::vector<int> > > mapTest;
    // fn(mapTest);
    // std::cout << mapTest[0].use_count() << "\n";
    int i = 3 << 2;
    i = (i >> 3) << 3;
    std::cout << i << "\n";

    // std::map<int, std::vector<int>* > mapTest;
    // gn(mapTest);
    // std::cout << mapTest.size() << "\n";
    return 0;
}