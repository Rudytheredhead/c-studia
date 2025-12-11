#include "Laptop.h"
#include <iostream>
#include <string>

Laptop::Laptop() : Komputer(), masa(2.5), czasBaterii(120) {

}

// 2. Konstruktor z 3 parametrami
Laptop::Laptop(std::string nazwa, int wiek, double cena) 
    : Komputer(nazwa, wiek, cena), masa(2.5), czasBaterii(120) {
}

// 3. Konstruktor z 5 parametrami
Laptop::Laptop(std::string nazwa, int wiek, double cena, double masa, int czasBaterii)
    : Komputer(nazwa, wiek, cena), masa(masa), czasBaterii(czasBaterii) {
  
}

double Laptop::GetMasa() const {
    return masa;
}

void Laptop::SetMasa(double m) {
    this->masa = m;
}

int Laptop::GetCzasBaterii() const {
    return czasBaterii;
}

void Laptop::SetCzasBaterii(int cb) {
    this->czasBaterii = cb;
}

void Laptop::Wypisz() {
    Komputer::Wypisz(); 
    
    std::cout << "Masa: " << masa << " kg, Bateria: " << czasBaterii << " min" << std::endl;
}