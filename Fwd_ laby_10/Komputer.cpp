#include"Komputer.h"

#include<string>
#include<iostream>


Komputer::Komputer(std::string nazwa, int wiek, double cena){
    this->nazwa=nazwa;
    this->wiek=wiek;
    this->cena=cena;
}

double Komputer::GetCena(){
    return cena;
}

int Komputer::GetWiek(){
    return wiek;
} 

std::string Komputer::GetNazwa(){
    return nazwa;
}

void Komputer::SetCena(double c){
    this->cena=c;
}

void Komputer::SetWiek(int w){
    this->wiek=w;
}

void Komputer::SetNazwa(std::string n){
    this->nazwa=n;
}

void Komputer::Wypisz(){
    std::cout<<"Nazwa: "<<nazwa<<" Wiek: "<<wiek<<" Cena: "<<cena<<std::endl;
}