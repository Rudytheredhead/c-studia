#include <iostream>
#include <string>
#include "Figura.h"
using namespace std;
int Figura::count = 0;

Figura::Figura(){
    liczba_bokow =3;
    color = "czerwony";
    count ++;
}
Figura::Figura(int liczba_bokow, string color){
    this -> liczba_bokow = liczba_bokow;
    this -> color = color;
    count ++;
}
void Figura::wypisz_count(){
    cout<<count<<endl;
}
void Figura::zmien_color(string color){
    this -> color = color;
}
void Figura::zmien_liczbe_bokow(int liczba_bokow){
    this -> liczba_bokow = liczba_bokow;
}