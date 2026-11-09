#include <iostream>

int main() {
    int* p = new int(42);
    std::cout << "valeur = " << *p << std::endl;
    delete p;
    return 0;
}
