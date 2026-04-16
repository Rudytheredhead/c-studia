#include"Obliczanie.h"
#include<algorithm>
#include <thread>
 #include <vector>
#include <functional>
#include <memory> 
#include<cmath>
#include<execution>
#include <numeric>


Srednia::Srednia(const iter &pocz,const iter&konc): pocz_(pocz), konc_(konc) {
        n_ = konc_-pocz_;
    }
void Srednia::operator() (){
        srednia_ =0.0;
        std::for_each(pocz_,konc_,[this](const double &x){srednia_+=x;});}

Suma_roznic::Suma_roznic(const iter &pocz,const iter&konc,double srednia): pocz_(pocz), konc_(konc),srednia_(srednia) {
        n_ = konc_-pocz_;
    }
void Suma_roznic::operator() (){
        suma_ =0.0;
        std::for_each(pocz_,konc_,[this](const double &x){suma_+=(x - srednia_)*(x - srednia_) ;});}
std::pair<double,double> licz_sam_podzial (const std::vector<double>& dane, int p) 
{
    // 1. Zabezpieczenia na wejściu
    if (dane.empty()) return {0.0,0.0}; 
    if (p <= 0) p = 1; 
    std::vector<std::unique_ptr<Srednia>> srednie;
    std::vector<std::unique_ptr<Suma_roznic>> sumy;

    std::vector<std::thread> watki;

    int n = dane.size();

    for (int i = 0; i < p; ++i) {
        srednie.push_back(std::make_unique<Srednia>(
            dane.begin() + n * i / p, 
            dane.begin() + n * (i + 1) / p
        ));
    }
    for (const auto& s : srednie) {
        watki.emplace_back(std::ref(*s));
    }
    for (auto& w : watki) {
        if (w.joinable()) {
            w.join();
        }
    }
    double srednia = 0.0;
    for (const auto& s : srednie) {
        srednia += s->wartosc() * s->ilosc();
    }
    srednia /=n;

    for (int i = 0; i < p; ++i) {
        sumy.push_back(std::make_unique<Suma_roznic>(
            dane.begin() + n * i / p, 
            dane.begin() + n * (i + 1) / p,
            srednia
        ));
    }
    for (const auto& s : sumy) {
        watki.emplace_back(std::ref(*s));
    }
    for (auto& w : watki) {
        if (w.joinable()) {
            w.join();
        }
    }
    double suma = 0.0;
    for (const auto& s : sumy) {
        suma += s->wartosc() * s->ilosc();
    }
    double std = std::sqrt(suma/(n-1));
    return {srednia,std};


}

std::pair<double,double> liczenie_auto(std::vector<double>& data) {
    const size_t n = data.size();
    if (n <= 1) return {0.0, 0.0};

    double suma = std::reduce(std::execution::par, data.begin(), data.end(), 0.0);
    double srednia = suma / n;


    double suma_kwadratow = std::transform_reduce(
        std::execution::par,
        data.begin(), data.end(),
        0.0,
        std::plus<double>(), // Operacja redukcji (dodawanie wyników)
        [srednia](double x) {return (x - srednia)*(x - srednia);} // Operacja transformacji (kwadrat różnicy)
        
    );
    double std  = std::sqrt(suma_kwadratow / (n - 1));

    return {srednia, std};
}

std::pair<double,double> liczenienie_jeden(std::vector<double>& data){
    double srednia = 0.0; 
    std::for_each(data.begin(),data.end(),[&srednia](const double &x){srednia+=x;});
    if (!data.empty())
        srednia /= data.size();
    else srednia = 0.0; 
    double wariancja = 0.0;
    std::for_each(data.begin(),data.end(),[&wariancja,srednia](const double &x){wariancja+=(srednia - x)*(srednia - x);});
    if (data.size()>1)
        wariancja/=(data.size()-1);
    else wariancja = 0.0;
    return {srednia,std::sqrt(wariancja)};
}