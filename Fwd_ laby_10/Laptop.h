#ifndef LAPTOP_H
#define LAPTOP_H

#include "Komputer.h"
#include <iostream>
#include <string>

class Laptop : public Komputer {
private:
    double masa;
    int czasBaterii;

public:
    Laptop();

    Laptop(std::string nazwa, int wiek, double cena);

    Laptop(std::string nazwa, int wiek, double cena, double masa, int czasBaterii);

    double GetMasa() const;
    void SetMasa(double m);

    int GetCzasBaterii() const;
    void SetCzasBaterii(int cb);

    void Wypisz();
};

#endif