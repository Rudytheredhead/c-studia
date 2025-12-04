#include "Wektor.h"

#include<string>
#include<iostream>

int main()
{
    float dane[]={ 10.5, 5.0, 2.5, 1.0};
    Wektor A(4, dane);

    Wektor B(A);

    std::cout << "Wektor A (konstruktor wlasciwy): " << A << std::endl;
    std::cout << "Wektor B po wpisaniu danych: " << B << std::endl;


    Wektor C=B;
    std::cout << "Wektor C: " << C << std::endl;

    Wektor D(5);
    D=A;
    std::cout << "Wektor D:" << D << std::endl;


    Wektor wynikdod= A+B;
    std::cout << "Wektor dodawania:" << wynikdod << std::endl;

    Wektor wynikod= A-B;
    std::cout << "Wektor odejmowania:" << wynikod << std::endl;


    int indeks;
    std::cout << "Podaj indeks wektora B, do ktorego chcesz uzyskac dostep (0-3): ";
    std::cin >> indeks;

    std::cout << "Wartosc elementu wektora B na pozycji [" << indeks << "]: " << B[indeks] << std::endl;


    B[0] = 99.0;
    std::cout << "Wektor B po modyfikacji elementu [0] na 99.0: " << B << std::endl;
    
    std::cout << "\n----------------------------------------\n";
    return 0;
}