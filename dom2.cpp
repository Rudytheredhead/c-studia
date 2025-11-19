#include <iostream>
#include <string>
#include "Figura.h"
using namespace std;



int main(){
    Figura::wypisz_count();
    Figura f1;
    f1.zmien_color("zielony");
    Figura::wypisz_count();

    return 0;
}