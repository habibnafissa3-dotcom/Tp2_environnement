#include <iostream>
int main() {
    int notes[3] = {10, 15, 17};
    int somme = 0;
    for (int i = 0; i <= 3; i++) {
        somme += notes[i];
    }
    std::cout << somme << std::endl;
}
