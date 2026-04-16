#ifndef OBL_H
#define OBL_H
#include<algorithm>
// #include <thread>
 #include <vector>
// #include <functional>
// #include <memory> 
// #include<iostream>


typedef std::vector<double>::const_iterator iter;
class Srednia{
    public:
    Srednia(const iter &pocz,const iter&konc);
    double wartosc()const {return srednia_;}
    void operator() ();
    int ilosc () const {return n_;}
    private:
    double srednia_;
    int n_;
    iter pocz_;
    iter konc_;
};

class Suma_roznic{
    public:
    Suma_roznic(const iter &pocz,const iter&konc,double srednia);
    double wartosc()const {return suma_;}
    void operator() ();
    int ilosc () const {return n_;}
    private:
    double suma_;
    double srednia_;
    int n_;
    iter pocz_;
    iter konc_;
};

std::pair<double,double>  licz_sam_podzial (const std::vector<double>& dane, int p);
std::pair<double,double> liczenie_auto(std::vector<double>& data);
std::pair<double,double> liczenienie_jeden(std::vector<double>& data);






#endif 