#include "czlowiek.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(){
    

    Czlowiek cz1;
    char i[9]= "Kowalski";
    char n[6]= "Nowak";
    Czlowiek cz2(i, n);
    Czlowiek cz3(cz2);
    cz3.wypiszCzlowieka();
    return 0;
}