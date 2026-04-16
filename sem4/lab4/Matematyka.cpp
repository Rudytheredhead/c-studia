
#include "Matematyka.h"
#include <vector>
#include <SFML/Graphics.hpp>
float STALA = 1.0f;
float Dt = 0.2f;
#include <cmath>
#include <algorithm>
//const int DLUGOSC = 800;
void obliczenie_temp(std::vector<std::vector<float>>& grid){
    std::vector<std::vector<float>> grid_kopia = grid;
        for (int x = 0; x<DLUGOSC;x++){
            for(int y = 0; y<DLUGOSC;y++){
                double suma = 0.0;
                for (int dx = -1; dx<=1; dx++){
                    for (int dy = -1; dy<=1; dy++){
                        if  (dy == dx or dy == -dx){continue;}
                        if (x+dx <0 || x+dx >DLUGOSC-1 || y +dy <0 || y+dy >DLUGOSC-1){continue;}
                        suma+= grid_kopia[x][y] - grid_kopia[x+dx][y+dy];
            

                    }
                }
                grid[x][y] += -STALA*Dt*suma;
    }}
};

void USTAW_KOLOR(std::vector<sf::Uint8>& pixels,int x, int y,int R, int G, int B, int alpha){
    int idx =  (y * DLUGOSC + x) * 4;
    pixels[idx + 0] = R;   
    pixels[idx + 1] = G; 
    pixels[idx + 2] = B;   
    pixels[idx + 3] = alpha; 
}







WynikRGB kelvinToRGB(float kelvin) {
    // Temperatury poniżej 1000K nie emitują widzialnego światła
    if (kelvin < 1000.0f) {
        WynikRGB wynik;
        wynik.r = 0;
        wynik.g = 0;
        wynik.b = 0;
        return wynik;
    }

    float temp = kelvin / 100.0f;
    float r, g, b;

    // Obliczanie koloru Czerwonego
    if (temp <= 66.0f) {
        r = 255.0f;
    } else {
        r = temp - 60.0f;
        r = 329.698727446f * std::pow(r, -0.1332047592f);
    }

    // Obliczanie koloru Zielonego
    if (temp <= 66.0f) {
        g = temp;
        g = 99.4708025861f * std::log(g) - 161.1195681661f;
    } else {
        g = temp - 60.0f;
        g = 288.1221695283f * std::pow(g, -0.0755148492f);
    }

    // Obliczanie koloru Niebieskiego
    if (temp >= 66.0f) {
        b = 255.0f;
    } else {
        if (temp <= 19.0f) {
            b = 0.0f;
        } else {
            b = temp - 10.0f;
            b = 138.5177312231f * std::log(b) - 305.0447927307f;
        }
    }

    // Zabezpieczenie (clamp) przed wyjściem poza zakres 0-255
    WynikRGB wynik;
    wynik.r = static_cast<unsigned char>(std::clamp(r * 255.0f, 0.0f, 255.0f));
    wynik.g = static_cast<unsigned char>(std::clamp(g * 255.0f, 0.0f, 255.0f));
    wynik.b = static_cast<unsigned char>(std::clamp(b * 255.0f, 0.0f, 255.0f));

    return wynik;
}

void zmiania_temp_na_rgb(std::vector<std::vector<float>>& grid, std::vector<sf::Uint8>& pixels) {
    for(int x = 0; x<DLUGOSC-1;x++){
        for (int y = 0;y<DLUGOSC-1;y++){
            float temp = grid[x][y];
            WynikRGB kolor = kelvinToRGB(temp);
            
            USTAW_KOLOR(pixels, x,y,kolor.r,kolor.g,kolor.b);
        }
    }
}