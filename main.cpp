#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

// Struktura reprezentująca punkt 2D 
struct Punkt {
    double x, y;
    bool operator<(const Punkt& inny) const {
        if (x != inny.x) return x < inny.x;
        return y < inny.y;
    }
};

// licze iloczyn wektorowy
double iloczyn_wektorowy(Punkt a, Punkt b, Punkt c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// funckja pomocnicza liczenia odleglosci
double dystans(Punkt p1, Punkt p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Komparator dla sortowania po współrzędnej Y
bool sortujPoY(Punkt a, Punkt b) {
    return a.y < b.y;
}

// zad 2.1: OTOCZKA WYPUKŁA 
vector<Punkt> wyznacz_otoczke(vector<Punkt> punkty) {
    int n = punkty.size();
    if (n <= 3) return punkty;
    sort(punkty.begin(), punkty.end());
    vector<Punkt> h;

    for (int i = 0; i < n; ++i) {
        while (h.size() >= 2 && iloczyn_wektorowy(h[h.size()-2], h[h.size()-1], punkty[i]) <= 0) h.pop_back();
        h.push_back(punkty[i]);
    }
    size_t lower_size = h.size();
    for (int i = n - 2; i >= 0; i--) {
        while (h.size() > lower_size && iloczyn_wektorowy(h[h.size()-2], h[h.size()-1], punkty[i]) <= 0) h.pop_back();
        h.push_back(punkty[i]);
    }
    if (h.size() > 1) h.pop_back();
    return h;
}

// zad 2.3: NAJBLIŻSZA PARA PUNKTÓW 
double najblizsza_para_rek(vector<Punkt>& Px, int start, int koniec, Punkt& p1_res, Punkt& p2_res) {
    if (koniec - start <= 3) {
        double min_d = 1e18;
        for (int i = start; i < koniec; ++i) {
            for (int j = i + 1; j < koniec; ++j) {
                double d = dystans(Px[i], Px[j]);
                if (d < min_d) {
                    min_d = d;
                    p1_res = Px[i];
                    p2_res = Px[j];
                }
            }
        }
        return min_d;
    }

    int mid = start + (koniec - start) / 2;
    Punkt punkt_podzialu = Px[mid];
    Punkt pL1, pL2, pP1, pP2;
    double dL = najblizsza_para_rek(Px, start, mid, pL1, pL2);
    double dP = najblizsza_para_rek(Px, mid, koniec, pP1, pP2);

    double d;
    if (dL < dP) { d = dL; p1_res = pL1; p2_res = pL2; }
    else { d = dP; p1_res = pP1; p2_res = pP2; }

    vector<Punkt> pas;
    for (int i = start; i < koniec; i++) {
        if (abs(Px[i].x - punkt_podzialu.x) < d) pas.push_back(Px[i]);
    }

    sort(pas.begin(), pas.end(), sortujPoY);

    for (size_t i = 0; i < pas.size(); i++) {
        for (size_t j = i + 1; j < pas.size() && (pas[j].y - pas[i].y) < d; j++) {
            double dist = dystans(pas[i], pas[j]);
            if (dist < d) {
                d = dist;
                p1_res = pas[i];
                p2_res = pas[j];
            }
        }
    }
    return d;
}

int main(int argc, char* argv[]) {
    // Sprawdzenie czy podano plik jako argument [cite: 47]
    if (argc < 2) { 
        cout << "Blad: Nie podano pliku wejsciowego!" << endl;
        cout << "Uzycie: .\\main.exe dane.txt" << endl;
        return 1; 
    }

    ifstream plik(argv[1]);
    if (!plik.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku " << argv[1] << endl;
        return 1;
    }

    int n;
    if (!(plik >> n)) return 1; // Wczytanie liczby punktów [cite: 49]
    vector<Punkt> punkty;
    for (int i = 0; i < n; i++) {
        Punkt p;
        if (plik >> p.x >> p.y) punkty.push_back(p); // Wczytanie współrzędnych [cite: 50]
    }
    plik.close();

    // 1. Wyznaczanie Otoczki [cite: 35, 53]
    vector<Punkt> otoczka = wyznacz_otoczke(punkty);
    cout << "Otoczka: ";
    for (size_t i = 0; i < otoczka.size(); ++i) {
        cout << "(" << fixed << setprecision(1) << otoczka[i].x << ", " << otoczka[i].y << ") ";
    }
    cout << endl;

    // 2. Najbliższe punkty [cite: 46, 55]
    sort(punkty.begin(), punkty.end());
    Punkt b1, b2;
    double min_dist = najblizsza_para_rek(punkty, 0, punkty.size(), b1, b2);
    cout << "Najblizsze Punkty: [(" << b1.x << ", " << b1.y << "), (" 
         << b2.x << ", " << b2.y << ")] d=" << fixed << setprecision(3) << min_dist << endl;

    return 0;
}
