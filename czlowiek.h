#ifndef CZLOWIEK_H
#define CZLOWIEK_H
#include <string>
using namespace std;
class Czlowiek{
private:
    char *imie; 
    char *nazwisko; 
    public:         
    Czlowiek();
    Czlowiek(char*, char*);
    Czlowiek(const Czlowiek &);
    ~Czlowiek();
    void wypiszCzlowieka();
    //void zmienNazwisko(char*);

};

#endif