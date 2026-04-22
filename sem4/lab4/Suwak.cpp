#include"Suwak.h"
#include <SFML/Graphics.hpp>

Suwak::Suwak(float x, float y, float szerokosc, float wysokosc, float min_v, float max_v, float start_v): 
    min_(min_v), max_(max_v), wartosc_(start_v), czy_ciagniety_(false)
    {
        tlo_.setPosition(x,y);
        tlo_.setSize(sf::Vector2f(szerokosc,wysokosc));
        tlo_.setFillColor(sf::Color(80,80,80));

        uchwyt_.setSize(sf::Vector2f(szerokosc/5.0f,wysokosc*1.5f));
        uchwyt_.setOrigin(uchwyt_.getSize().x/2.0f, uchwyt_.getSize().y/2.0f);
        uchwyt_.setFillColor(sf::Color::White);

        aktualizujPozycjeUchwytu();
    }

        
void Suwak::aktualizujPozycjeUchwytu(){
    float procent = (wartosc_ - min_)/ (max_- min_);
    float x = tlo_.getPosition().x + procent*tlo_.getSize().x;
    float y= tlo_.getPosition().y + tlo_.getSize().y/2.0f;
    uchwyt_.setPosition(x,y);
}

 
void Suwak::aktualizujWartosc(float mouse_x){
    float tlo_x = tlo_.getPosition().x;
    float szerokosc = tlo_.getSize().x;
    if (mouse_x<tlo_x) mouse_x = tlo_x;
    if (mouse_x>szerokosc+ tlo_x) mouse_x =szerokosc + tlo_x;
    float procent = (mouse_x - tlo_x)/szerokosc;
    wartosc_ = min_  + procent*(max_-min_);
    aktualizujPozycjeUchwytu();

}
void Suwak::sprawdzZdarzenia(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if( uchwyt_.getGlobalBounds().contains(mousePos) || tlo_.getGlobalBounds().contains(mousePos) ){
            czy_ciagniety_ = true;
            aktualizujWartosc(mousePos.x);  
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
        czy_ciagniety_ = false;
    }
    else if (event.type == sf::Event::MouseMoved && czy_ciagniety_){
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        aktualizujWartosc(mousePos.x);

    }

}