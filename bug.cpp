#include <iostream>
#include <vector>

double moyenne(const std::vector<int>& notes)
{
    double somme = 0.0;
    for (std::size_t i = 0; i < notes.size(); ++i) {
        somme += notes[i];
    }
    return somme / notes.size();
}

int main()
{
    std::vector<int> notes = {12, 14, 16};
    std::cout << moyenne(notes) << std::endl;
    return 0;
}
