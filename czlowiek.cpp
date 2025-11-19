#include "czlowiek.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

Czlowiek::Czlowiek(){
    this -> imie = nullptr;
    this -> nazwisko = nullptr;
}
Czlowiek::Czlowiek(char* _imie, char* _nazwisko){
    this -> imie = new char[strlen(_imie)+1];
    strcpy(imie,_imie);
    this ->nazwisko = new char[strlen(_nazwisko)+1];
    strcpy(nazwisko,_nazwisko);
}
Czlowiek::Czlowiek(const Czlowiek &drugi){
    this -> imie = new char[strlen(drugi.imie)+1];
    strcpy(imie,drugi.imie);
    this ->nazwisko = new char[strlen(drugi.nazwisko)+1];
    strcpy(nazwisko,drugi.nazwisko);

}

Czlowiek::~Czlowiek() {
    delete[] imie;
    delete[] nazwisko;
}
void Czlowiek::wypiszCzlowieka(){
    cout<<imie<<" "<<nazwisko<<endl;
}