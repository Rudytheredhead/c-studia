#ifndef DANE_STAT_H
#define DANE_STAT_H
#include <string>
#include<vector>
#include <iostream>
#include <memory>
class Plik{
    
    public: 
    virtual const std::vector<float>& daj_dane() const =0; 
    //dwa consty zeby zapobiec zmoywikoaniu po ref
    virtual ~Plik() = default; //deafultowy destruktor wygenerowany przez kompilator

};

class Plik_real: public Plik{
    public: 
    Plik_real (std::string sciezka_do_pliku); //faktyczne wczytywanie danych z pliku
    const std::vector<float>& daj_dane() const{return dane_;}//zwraca ref do danych
    
    private: 
    std::vector<float> dane_;
};

class Plik_proxy: public Plik{
    private:
    mutable std::unique_ptr<Plik> plik_;//mogacy zmieniac typ zmianna, dzieki mutable dalej moze byc cosnt
    //na poczatku jest pusty - zwykly plik, potem przy pierwszej inicjaji zmieania sie w plikreal
    std::string nazwa_pliku_;
    public:
    Plik_proxy (std::string nazwa): nazwa_pliku_(nazwa), plik_(nullptr){}//nullptr nowoczesna wersji NULL
    virtual const std::vector<float>& daj_dane () const {
        if (!plik_){ //sprawdza czy plik istnieje, jezli nie wywsouluje kosntruktor z plik real
            plik_ = std::make_unique<Plik_real>(nazwa_pliku_);}
        return plik_ ->daj_dane();
    }
};
#endif 