#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
enum class Mention { Ajourne, Passable, AssezBien, Bien, TresBien };

constexpr double NOTE_MIN = 0.0;
constexpr double NOTE_MAX = 20.0;
constexpr double SEUIL_ADMIS = 10.0;
constexpr int NB_MIN_ETUDIANTS = 1;
constexpr int NB_MAX_ETUDIANTS = 200;
constexpr int NB_MENTIONS = 5;

Mention determinerMention(double note) {
    if (note < 10.0) return Mention::Ajourne;
    if (note < 12.0) return Mention::Passable;
    if (note < 14.0) return Mention::AssezBien;
    if (note < 16.0) return Mention::Bien;
    return Mention::TresBien;
}

std::string nomMention(Mention m) {
    switch (m) {
        case Mention::Ajourne: return "Ajourne";
        case Mention::Passable: return "Passable";
        case Mention::AssezBien: return "Assez bien";
        case Mention::Bien: return "Bien";
        case Mention::TresBien: return "Tres bien";
    }
    return "";
}

// Pour accepter 12,5 -> on remplace , par .
double lireNote(int i) {
    std::string texte{};
    double note = 0.0;
    while (true) {
        std::cout << "Note de l'etudiant " << (i + 1) << " : ";
        if (!(std::cin >> texte)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entree invalide, recommence.\n";
            continue;
        }
        for (char &c : texte) {
            if (c == ',') c = '.';
        }
        try {
            size_t pos = 0;
            note = std::stod(texte, &pos);
            if (pos != texte.size()) throw std::invalid_argument("reste");
        } catch (...) {
            std::cout << "Entree invalide, recommence.\n";
            continue;
        }
        if (note < NOTE_MIN || note > NOTE_MAX) {
            std::cout << "Note hors de [0, 20], recommence.\n";
            continue;
        }
        return note;
    }
}

int main() {
    std::string nomUE{};
    std::cout << "Nom de l'UE : ";
    std::getline(std::cin, nomUE);
    if (nomUE.empty()) std::getline(std::cin, nomUE);

    int nb = 0;
    while (true) {
        std::cout << "Nombre d'etudiants (1-200) : ";
        if ((std::cin >> nb) && nb >= NB_MIN_ETUDIANTS && nb <= NB_MAX_ETUDIANTS) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Nombre invalide, recommence.\n";
    }

    std::vector<double> notes{};
    notes.reserve(static_cast<size_t>(nb));

    double somme = 0.0;
    double minNote = NOTE_MAX;
    double maxNote = NOTE_MIN;

    for (int i = 0; i < nb; ++i) {
        double note = lireNote(i);
        notes.push_back(note);
        somme += note;
        if (note < minNote) minNote = note;
        if (note > maxNote) maxNote = note;
    }

    double moyenne = somme / static_cast<double>(nb);

    double sommeCarres = 0.0;
    int nbAdmis = 0;
    int compteurs[NB_MENTIONS] = {0, 0, 0, 0, 0};

    for (double n : notes) {
        double diff = n - moyenne;
        sommeCarres += diff * diff;
        if (n >= SEUIL_ADMIS) ++nbAdmis;
        Mention m = determinerMention(n);
        compteurs[static_cast<int>(m)]++;
    }

    double ecartType = std::sqrt(sommeCarres / static_cast<double>(nb));
    double pourcentage = static_cast<double>(nbAdmis) * 100.0 / static_cast<double>(nb);

    std::cout << "\nStatistiques - " << nomUE << " (" << nb << " etudiants)\n";
std::cout << std::fixed << std::setprecision(2);
std::cout << "Note minimale : " << minNote << "\n";
std::cout << "Note maximale : " << maxNote << "\n";
std::cout << "Moyenne : " << moyenne << "\n";
std::cout << "Ecart-type : " << ecartType << "\n";
std::cout << std::setprecision(1);
std::cout << "Admis : " << nbAdmis << " (" << pourcentage << " %)\n";
std::cout << std::defaultfloat;
   std::cout << "\nRepartition par mention\n";
    for (int i = 0; i < NB_MENTIONS; ++i) {
        Mention m = static_cast<Mention>(i);
        std::string etoiles(static_cast<size_t>(compteurs[i]), '*');
        std::cout << nomMention(m) << " " << etoiles << " (" << compteurs[i] << ")\n";
    }
    return 0;
}