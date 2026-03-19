#include"dane_stat.h"
#include <string>
#include <fstream>
#include <algorithm>
#include<iostream>

//faktyczne whrywanie pliku z proxy
Plik_real::Plik_real(std::string sciezka_do_pliku){
    

    //ustawianie wilekosci vectora
    //mozna bylo pow() ale zwraca double i tak bedzie bardziej optyym,alnie
    
    int ilosc0 = std::count(sciezka_do_pliku.begin(),sciezka_do_pliku.end(),'0');
    
    auto oblicz_rozmiar = [] (int liczba_0) ->size_t{
        size_t wynik = 1;
        for (int i =0;i<liczba_0+3;i++){
            wynik*=10;
        }
        std::cout<<wynik;
        return wynik;

    };
    dane_.reserve(oblicz_rozmiar(ilosc0));
    std::ifstream plik(sciezka_do_pliku); 
    float liczba;
    while (plik >> liczba){
        dane_.push_back(liczba);
    }
    std::cout<<"wczytano dane"<<std::endl;
}
