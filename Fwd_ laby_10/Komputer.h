#ifndef KOMPUTER_H
#define KOMPUTER_H

#include<iostream>
#include<string>

class Komputer{
protected:
std::string nazwa;
int wiek;
double cena;

public:
Komputer(std::string nazwa="X", int wiek=1, double cena=2000);
virtual ~Komputer(){};

double GetCena();
int GetWiek();
std::string GetNazwa();

void SetCena(double c);
void SetWiek(int w);
void SetNazwa(std::string n);

virtual void Wypisz();


};

#endif