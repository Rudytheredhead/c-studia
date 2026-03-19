#include <iostream>
#include "Wektor3D.h"


int main ()
{
    Wektor3D w1 (2, 4, 6);
    std::cout << "Mamy wektor w1: " << w1 << std::endl;
    std::cout << "Podaj swoj wektor w2: ";
    Wektor3D w2;
    std::cin >> w2;

    if (w1 == w2)
        std::cout << "Smieszne! Podales taki sam wektor!" << std::endl;

    double skalarny = w1 * w2;
    Wektor3D wektorowy = w1 % w2;
    Wektor3D suma = w1 + w2;
    Wektor3D roznica = w2 - w1;

    std::cout << "Iloczyn skalarny wynosi: " << skalarny << std::endl;
    std::cout << "Iloczyn wektorowy wynosi: " << wektorowy << std::endl;
    std::cout << "Suma wynosi: " << suma << std::endl;
    std::cout << "Roznica wynosi: " << roznica << std::endl;

    std::cout << "Dwukrotnosc wektora " << w2 << " wynoi " << 2*w2 << std::endl;

    const Wektor3D w3 = w2;

    double abs = w3.modul();    // długość wektora
    double abs2 = w3.modul2();  // kwadrat długości

    std::cout << "Dlugosc wektora " << w3 << " wynoi " << abs << std::endl;
    std::cout << "Kwadrat dlugosci wektora " << w3 << " wynoi " << abs2 << std::endl;

    if (w3.x() < 0)     // z rozpędu dostarcz także metody y() oraz z()
        std::cout << "Intrygujace! Wektor " << w3 << " ma ujemna skladowa iksowa" << std::endl;
}