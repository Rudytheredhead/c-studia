#ifndef MAT_H
#define MAT_H



#include <vector>
#include <SFML/Graphics.hpp>
struct WynikRGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
WynikRGB kelvinToRGB(float kelvin);

const int DLUGOSC = 800;
const int LICZBA_WATKOW = 4;

const float szerokosc = 200.0f;
const float x_moc= DLUGOSC/4.0f - szerokosc/2.0f;
const float x_promien = 3.0f*DLUGOSC/4.0f - szerokosc/2.0f;

void obliczenie_temp(const std::vector<float>& grid_in, std::vector<float>& grid_out,int start);
inline void USTAW_KOLOR(std::vector<sf::Uint8>& pixels,int x, int y,int R, int G, int B, int alpha = 255);
void zmiania_temp_na_rgb(std::vector<float>& grid, std::vector<sf::Uint8>& pixels);   
void podgrzewanie_grida(std::vector<std::pair<int,int>>&idxy,std::vector<float>&  grid_A,std::vector<float>&  grid_B,float moc,float promien);

#endif 
