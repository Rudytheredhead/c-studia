#include <iostream>
#include <cmath>
#include <vector>

// --- KLASA FIGURA ---
class Figura {
protected:
    float x, y;

public:
    Figura(float px = 0, float py = 0) : x(px), y(py) {}
    virtual ~Figura() {}

    // Metody czysto wirtualne - klasa staje się abstrakcyjna
    virtual void Wypisz() = 0;
    virtual float Pole() = 0; 
};

// --- KLASA OKRAG ---
class Okrag : public Figura {
private:
    float r;

public:
    // Konstruktor domyślny
    Okrag() : Figura(0, 0), r(0) {}

    // Konstruktor inicjalizujący
    Okrag(float px, float py, float pr) : Figura(px, py), r(pr) {}

    void Wypisz() override {
        std::cout << "Okrag (x,y,R)" << std::endl;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        std::cout << r << std::endl;
    }

    float Pole() override {
        return M_PI * r * r;
    }
};


void WypiszIPole(Figura* f) {
    if (f == nullptr) return; // Dobra praktyka: sprawdzenie czy wskaźnik nie jest pusty

    // Wywołanie metody wirtualnej Wypisz
    f->Wypisz();

    // Wyświetlenie pola obliczonego przez odpowiednią klasę pochodną
    std::cout << "Pole tej figury wynosi: " << f->Pole() << std::endl;
    std::cout << "-----------------------" << std::endl;
}


int main() {
    // 6.1. Deklaracja wektora wskaźników do klasy bazowej
    // Wektor przechowuje "adresy", dzięki czemu zadziała polimorfizm
    std::vector<Figura*> figury;

    // 6.2. Dynamiczne dodawanie obiektów (na stertę)
    figury.push_back(new Okrag());           // Okrąg domyślny (0,0,0)
    figury.push_back(new Okrag(2, 2, 5));    // Okrąg (2,2,5)
    
    // Możesz tu dodać inne figury w przyszłości, np.:
    // figury.push_back(new Kwadrat(0, 0, 4));

    std::cout << "--- PRZEGLAD KOLEKCJI FIGUR ---" << std::endl;

    // 6.3. Iteracja po kontenerze
    // Używamy pętli for-each (zakresowej)
    for (Figura* f : figury) {
        f->Wypisz(); // Wywołuje odpowiednie Wypisz() dla każdego obiektu
        std::cout << "Pole: " << f->Pole() << std::endl;
        std::cout << "-----------------------" << std::endl;
    }

    // 6.4. Zwolnienie pamięci
    // Ponieważ użyliśmy 'new', musimy ręcznie wywołać 'delete' dla każdego elementu
    for (Figura* f : figury) {
        delete f;
    }
    
    // Dobra praktyka: wyczyść wektor po usunięciu obiektów
    figury.clear();

    return 0;
}