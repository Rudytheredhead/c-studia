#include <iostream>
#include "Komputer.h"
#include "Desktop.h"
#include "Laptop.h"

int main() {
    Komputer k1("Baza", 2, 1500);

    Desktop d1;
    Desktop d2("Biuro", 3, 2000, "Intel HD");
    Desktop d3("Gaming", 1, 4500, "RTX 3060");

    Laptop l1;
    Laptop l2("Ultrabook", 2, 3500);
    Laptop l3("Pro", 1, 6000, 2.1, 240);

    Komputer* wskKomputer = new Komputer("Wsk_Komp", 4, 1000);
    Desktop* wskDesktop = new Desktop("Wsk_Desk", 2, 2500, "GTX 1650");
    Laptop* wskLaptop = new Laptop("Wsk_Lap", 1, 4000, 1.5, 180);

    k1.Wypisz();

    d1.Wypisz();
    d2.Wypisz();
    d3.Wypisz();

    l1.Wypisz();
    l2.Wypisz();
    l3.Wypisz();

    wskKomputer->Wypisz();
    wskDesktop->Wypisz();
    wskLaptop->Wypisz();

    delete wskKomputer;
    delete wskDesktop;
    delete wskLaptop;

    return 0;
}