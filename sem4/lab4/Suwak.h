#ifndef SUW_H
#define SUW_H
#include <SFML/Graphics.hpp>
class Suwak{
private:
    sf::RectangleShape tlo_;
    sf::RectangleShape uchwyt_;
    float min_;
    float max_;
    float wartosc_;
    bool czy_ciagniety_;
public:
    Suwak(float x, float y, float szerokosc, float wysokosc, float min_v, float max_v, float start_v);
    void aktualizujPozycjeUchwytu();
    void aktualizujWartosc(float mouse_x);
    void rysuj(sf::RenderWindow &window) {window.draw(tlo_); window.draw(uchwyt_);};
    float pobierz_wartosc(){return wartosc_;};
    void sprawdzZdarzenia(const sf::Event& event, const sf::RenderWindow& window);
    bool czy_ciagniety(){return czy_ciagniety_;};



};
#endif 