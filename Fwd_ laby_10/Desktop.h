#ifndef DESKTOP_H
#define DESKTOP_H

#include "Komputer.h"
#include <iostream>
#include <string>

class Desktop : public Komputer {
private:
    std::string kartaGraficzna;

public:
    Desktop(); 

    Desktop(std::string nazwa, int wiek, double cena, std::string kartaGraficzna);

    std::string GetKartaGraficzna() const; 
    void SetKartaGraficzna(std::string w);

    void Wypisz();
};

#endif