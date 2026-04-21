
#include "Matematyka.h"
#include <vector>
#include <SFML/Graphics.hpp>
const float STALA = 50.0f;
const float Dt = 0.005f; // Przy tych parametrach jedna iteracja pętli = 0.02 sekundy czasu fizycznego
#include <cmath>
#include <algorithm>
#include<iostream> //do usniecia
//const int DLUGOSC = 800;
void obliczenie_temp(const std::vector<std::vector<float>>& grid_in, std::vector<std::vector<float>>& grid_out) {
    // Pętle od 1 do DLUGOSC-1 gwarantują, że nie wyjdziemy poza tablicę.
    // Brzegi pozostaną nieruszone (będą pełnić rolę izolacji/stałej temperatury).
    for (int x = 1; x < DLUGOSC - 1; x++) {
        for(int y = 1; y < DLUGOSC - 1; y++) {
            
            // Bezpośrednie wyliczenie różnic dla 4 sąsiadów (góra, dół, lewo, prawo).
            // To dokładnie to samo co Twoje pętle z dx/dy, ale miliony razy szybsze.
            float suma = 0.0f;
            suma += grid_in[x][y] - grid_in[x+1][y];
            suma += grid_in[x][y] - grid_in[x-1][y];
            suma += grid_in[x][y] - grid_in[x][y+1];
            suma += grid_in[x][y] - grid_in[x][y-1];
            
            // Zapis nowego stanu prosto do bufora wyjściowego
            grid_out[x][y] = grid_in[x][y] - STALA * Dt * suma;
        }
    }
}

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
    wynik.r = static_cast<unsigned char>(std::clamp(r , 0.0f, 255.0f));
    wynik.g = static_cast<unsigned char>(std::clamp(g , 0.0f, 255.0f));
    wynik.b = static_cast<unsigned char>(std::clamp(b , 0.0f, 255.0f));

    return wynik;
}

void zmiania_temp_na_rgb(std::vector<std::vector<float>>& grid, std::vector<sf::Uint8>& pixels) {
    for(int x = 0; x<DLUGOSC;x++){
        for (int y = 0;y<DLUGOSC;y++){
            float temp = grid[x][y];
            WynikRGB kolor = kelvinToRGB(temp);
            
            USTAW_KOLOR(pixels, x,y,kolor.r,kolor.g,kolor.b);
        }
    }
}

void podgrzewanie_grida(std::vector<std::pair<int,int>>&idxy, std::vector<std::vector<float>>& grid_A,std::vector<std::vector<float>>& grid_B,float moc,float promien){
    int r = static_cast<int>(promien);
    for (const auto pos:idxy){
        int mouse_x = pos.first;
        int mouse_y = pos.second;
        //std::cout<<mouse_x<<mouse_y;
        for (int dx = -r;dx<r+1;dx++){
            for (int dy= -r;dy <r+1;dy++){
                int x = mouse_x + dx;
                int y = mouse_y + dy;
                if (x>0 && x<DLUGOSC && y>0 && y<DLUGOSC ){
                    grid_A[x][y] += moc;
                    grid_B[x][y] += moc;


                }
            }
        }
    }
}