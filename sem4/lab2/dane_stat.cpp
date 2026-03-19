#include"dane_stat.h"
#include <string>
#include <fstream>
#include <algorithm>
#include<iostream>
#include <stdexcept> //biblioteka do wywalania bledow

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
        return wynik;
    };
    
    std::ifstream plik(sciezka_do_pliku); 
    if (!plik.is_open()){
        //gdy plik sie nie otworzy wywali blad z tym komuniakatem 
        throw std::runtime_error("Blad: Nie mozna otworzyc pliku: " + sciezka_do_pliku);   
    }

    float liczba;
    dane_.reserve(oblicz_rozmiar(ilosc0));
    while (plik >> liczba){
        dane_.push_back(liczba);
    }
    if (dane_.empty()){
        throw std::runtime_error("Blad w pobierniu danych z pliku "+sciezka_do_pliku);
    }
    std::cout<<"wczytano dane"<<std::endl;
}

Plik_proxy::Plik_proxy (std::string nazwa): nazwa_pliku_(nazwa), plik_(nullptr){//nullptr nowoczesna wersji NULL
    //szybko sprawdz czy plik istnieje
    //mozna bybylo if (fs::exists(sciezka)) z #include <filesystem> zeby bylo szybciej
    std::ifstream plik(nazwa_pliku_); 
    if (!plik.is_open()){
        throw std::runtime_error("Blad: Nie mozna otworzyc pliku: " + nazwa_pliku_);
    }
}