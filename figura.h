#ifndef FIGURA_H
#define FIGURA_H
#include <string>
using namespace std;
class Figura{

private:
    int liczba_bokow;
    
    string color;
public:
    static int count;
    Figura();
    Figura(int liczba_bokow, string color);
    static void wypisz_count();
    void zmien_color(string color);
    void zmien_liczbe_bokow(int liczba_bokow);


};

#endif