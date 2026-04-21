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
void obliczenie_temp(const std::vector<std::vector<float>>& grid_in, std::vector<std::vector<float>>& grid_out);
void USTAW_KOLOR(std::vector<sf::Uint8>& pixels,int x, int y,int R, int G, int B, int alpha = 255);
void zmiania_temp_na_rgb(std::vector<std::vector<float>>& grid, std::vector<sf::Uint8>& pixels);   
void podgrzewanie_grida(std::vector<std::pair<int,int>>&idxy, std::vector<std::vector<float>>& grid_A,std::vector<std::vector<float>>& grid_B,float moc,float promien);

#endif 
