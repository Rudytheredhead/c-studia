#include"rozklady.h"
#include <algorithm>
#include<iostream>
void Rozklad::get_estymator()const{
    for (const auto& [nazwa,wynik]:estymator_){
        std::cout<<nazwa<<" : "<<wynik<<std::endl;
    }
}
std::string Rozklad::get_nazwa()const{return nazwa_;}


//do liczenia sum mozna bylo by uzyc 
//float srednia = std::accumulate(dane.begin(), dane.end(), 0.0f)
//z biblioteki numeric zeby bylo szybciej 
namespace{ //jakby przypadkiem w innym pliku cpp pojawila sie ta sama funkcja 
constexpr auto policz_srednia = [] (const std::vector<float> &plik) ->float{ //constexpr -> zapobiega napisaniu funkcji
    float srednia = 0.0; 
    std::for_each(plik.begin(),plik.end(),[&srednia](const float &x){srednia+=x;});
    if (!plik.empty())
        srednia /= plik.size();
    else srednia = 0.0; //mozna byloby ewentualnie jakis blad wyrzucic czy cos takiego
    return srednia;
};

constexpr auto policz_wariancje = [](const std::vector<float> &plik,float srednia )-> float{
    float wariancja = 0.0;
    std::for_each(plik.begin(),plik.end(),[&wariancja,srednia](const float &x){wariancja+=(srednia - x)*(srednia - x);});
    if (plik.size()>1)
        wariancja/=(plik.size()-1);
    else wariancja = 0.0;
    return wariancja;
};
constexpr auto policz_mediane = [](const std::vector<float> &plik)->float{ //mozna uzyc nth_element z <alghoritm> zeby nie uzywac .sort()
    if (plik.empty()) return 0.0;
    std::vector<float> kopia_danych = plik; //trzeba zrobic lokalna kopie bo const, consta nie usuniemy bo jest to podklasa
    std::sort(kopia_danych.begin(),kopia_danych.end());
    size_t ilosc = kopia_danych.size();
    size_t idx = ilosc/2; //w cpp 5/2 to 2 wiec tez bedzie dzialac dla nieparzystych
    float mediana = 0.0;
    if (ilosc%2==0){
        mediana = (kopia_danych[idx]+kopia_danych[idx-1])/2.0f;
    }
    else{
        mediana = kopia_danych[idx];
    }
    return mediana;
};

}

RozkladGaussa::RozkladGaussa(const std::vector<float>&dane):Rozklad(dane){
    estymator_["srednia"] = policz_srednia(dane);
    estymator_["wariancja"] = policz_wariancje(dane,estymator_["srednia"]);
    estymator_["mediana"]= policz_mediane(dane);
    nazwa_ ="Gauss";
}

RozkladPoissona::RozkladPoissona(const std::vector<float>&dane):Rozklad(dane){
    estymator_["srednia"] = policz_srednia(dane);
    estymator_["wariancja"] = policz_wariancje(dane,estymator_["srednia"]);
    estymator_["mediana"]= policz_mediane(dane);
    nazwa_ ="Poisson";
}

RozkladLorentza::RozkladLorentza(const std::vector<float>&dane):Rozklad(dane){
    estymator_["srednia"] = policz_srednia(dane);
    estymator_["mediana"]= policz_mediane(dane);
    nazwa_ ="Lorentz";
}

const int RozkladGaussa::id = 1;
const int RozkladPoissona::id = 2;
const int RozkladLorentza::id = 3;

std::map<int, KreatorRozkladu> FabrykaRozkladow::rozklady;
std::map<int, std::string> FabrykaRozkladow::nazwy;


