#include"rozklady.h"
#include <algorithm>
float Rozklad::get_estymator()const{return estymator_;}
std::string Rozklad::get_nazwa()const{return nazwa_;}


//do liczenia sum mozna bylo by uzyc 
//float srednia = std::accumulate(dane.begin(), dane.end(), 0.0f)
//z biblioteki numeric zeby bylo szybciej 
RozkladGaussa::RozkladGaussa(const std::vector<float>&dane):Rozklad(dane){
    float srednia = 0.0;
    std::for_each(dane.begin(),dane.end(),[&srednia](const float &x){srednia+=x;});
    if (!dane.empty())
        estymator_ = srednia/dane.size();
    else
        estymator_ =0.0; //mozna byloby ewentualnie jakis blad wyrzucic czy cos takiego
    nazwa_ ="Gauss";
}

RozkladPoissona::RozkladPoissona(const std::vector<float>&dane):Rozklad(dane){
    float srednia = 0.0;
    std::for_each(dane.begin(),dane.end(),[&srednia](const float &x){srednia+=x;});
    if (!dane.empty())
        estymator_ = srednia/dane.size();
    else
        estymator_ = 0.0;
    nazwa_ ="Poisson";
}

RozkladLorentza::RozkladLorentza(const std::vector<float>&dane):Rozklad(dane){
    //trzeba zrobic lokalna kopie bo const, consta nie usuniemy bo jest to podklasa
    std::vector<float> kopia_danych = dane;
    std::sort(kopia_danych.begin(),kopia_danych.end());
    int ilosc = kopia_danych.size();
    int idx;
    
    if (ilosc%2==0){
        idx = ilosc/2;
        estymator_ = (kopia_danych[idx]+kopia_danych[idx-1])/2.0f;
    }
    else{
        idx = (ilosc-1)/2;
        estymator_ = kopia_danych[idx];
    }
    nazwa_ ="Lorentz";
}

const int RozkladGaussa::id = 1;
const int RozkladPoissona::id = 2;
const int RozkladLorentza::id = 3;

std::map<int, KreatorRozkladu> FabrykaRozkladow::rozklady;
std::map<int, std::string> FabrykaRozkladow::nazwy;


