
#include"Komputer.h"
#include"Desktop.h"
#include<iostream>
#include<string>


Desktop::Desktop(){
    nazwa="X";
    wiek=1;
    cena=2000;
    kartaGraficzna="Y";}

Desktop::Desktop(std::string nazwa, int wiek, double cena, std::string kartaGraficzna){
    this->nazwa=nazwa;
    this->wiek=wiek;
    this->cena=cena;
    this->kartaGraficzna=kartaGraficzna;
}

std::string Desktop::GetKartaGraficzna()const{
    return kartaGraficzna;
}

void Desktop::SetKartaGraficzna(std::string w){
    this->kartaGraficzna=w;
}

void Desktop::Wypisz(){
     std::cout<<"Nazwa: "<<nazwa<<" Wiek: "<<wiek<<" Cena: "<<cena<<" Karta Graficzna: "
     <<kartaGraficzna<<std::endl;
}