#include "Wektor.h"
#include <iostream>
#include <string>


Wektor::Wektor(int size):N(size){
    wspolrzedne=new float[N];
    for(int i=0; i<N; i++)
    {
        wspolrzedne[i]=0.0;
    }
}

Wektor::Wektor(int size, const float* data) :N(size)
{
    wspolrzedne = new float[N];
    for(int i=0; i<N; i++)
    {
        wspolrzedne[i]=data[i];
    } 
}

Wektor::Wektor(const Wektor &inny): N(inny.N)
{
    wspolrzedne=new float[N];

    for( int i=0; i<N; i++)
    {
        wspolrzedne[i]=inny.wspolrzedne[i];
    }
}

Wektor::~Wektor()
{
    delete[] wspolrzedne;
    wspolrzedne=nullptr;
}

float& Wektor::operator[](int indeks)
{
    return wspolrzedne[indeks];
}

Wektor Wektor::operator+(const Wektor &inny) const
{
    if(N!=inny.N){
        std::cout<<"Rozne dlugosci wektorow"<<std::endl;
        exit(1);
    }

    Wektor wynik(N);

    for(int i=0; i<N; i++)
    {
        wynik.wspolrzedne[i]= this->wspolrzedne[i]+inny.wspolrzedne[i];
    }
    return wynik;
}

Wektor Wektor::operator-(const Wektor &inny) const
{
    if(N!=inny.N){
        std::cout<<"Rozne dlugosci wektorow"<<std::endl;
        exit(1);
    }

    Wektor wynik(N);

    for(int i=0; i<N; i++)
    {
        wynik.wspolrzedne[i]= this->wspolrzedne[i]-inny.wspolrzedne[i];

    }
    return wynik;
}


std::ostream& operator<<(std::ostream& os, const Wektor& wektor) {
    os << "[";
    for (int i = 0; i < wektor.N; ++i) {
            os << wektor.wspolrzedne[i]; 
        
        if (i < wektor.N - 1) {
            os << ", ";
        }
    }

    os << "]";    
    return os; 
}

Wektor& Wektor::operator=(const Wektor &inny)
{
    if(this==&inny){
        return *this;
    }
    delete[] wspolrzedne;

    N=inny.N;

    wspolrzedne=new float[N];
    for(int i=0; i<N; i++)
    {   
        wspolrzedne[i]=inny.wspolrzedne[i];
    }
    return *this;
} 


