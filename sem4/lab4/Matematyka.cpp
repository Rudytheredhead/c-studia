
#include "Matematyka.h"
#include <vector>
#include <SFML/Graphics.hpp>
const float STALA = 50.0f;
const float Dt = 0.005f; // Przy tych parametrach jedna iteracja pętli = 0.02 sekundy czasu fizycznego
#include <cmath>
#include <algorithm>









void obliczenie_temp(const std::vector<float>& grid_in, std::vector<float>& grid_out,int start){
    int koniec = start + DLUGOSC/LICZBA_WATKOW;
    if (koniec ==DLUGOSC) koniec= DLUGOSC-1;
    // Pętle od 1 do DLUGOSC-1 gwarantują, że nie wyjdziemy poza tablicę.
    // Brzegi pozostaną nieruszone (będą pełnić rolę izolacji/stałej temperatury).
    


    for (int y = start; y < koniec; y++) {
        for(int x = 1; x < DLUGOSC - 1; x++) {
            
            // Bezpośrednie wyliczenie różnic dla 4 sąsiadów (góra, dół, lewo, prawo).
            // To dokładnie to samo co Twoje pętle z dx/dy, ale miliony razy szybsze.
            float suma = 0.0f;
            int idx = y*DLUGOSC +x;
            suma += grid_in[idx] - grid_in[idx+1];
            suma += grid_in[idx] - grid_in[idx-1];
            suma += grid_in[idx] - grid_in[idx+DLUGOSC];
            suma += grid_in[idx] - grid_in[idx-DLUGOSC];

            // Zapis nowego stanu prosto do bufora wyjściowego
          
            grid_out[y*DLUGOSC+x] = grid_in[y*DLUGOSC+x] - STALA * Dt * suma;
        }
    }
}

inline void USTAW_KOLOR(std::vector<sf::Uint8>& pixels,int x, int y,int R, int G, int B, int alpha){
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

// Słowo const chroni tablicę przed przypadkową modyfikacją w trakcie działania programu
const std::vector<WynikRGB> mapa_temperatur = []() {
    std::vector<WynikRGB> lut(max_temp);
    for (int temp = 0; temp < max_temp; temp++) {
        lut[temp] = kelvinToRGB(static_cast<float>(temp));
    }
    return lut;
}(); // Te nawiasy () na końcu sprawiają, że funkcja od razu się wykonuje i zwraca wynik

void zmiania_temp_na_rgb(std::vector<float>& grid, std::vector<sf::Uint8>& pixels)  {
    for(int y = 0; y<DLUGOSC;y++){
        for (int x = 0;x<DLUGOSC;x++){
            int temp = static_cast<int>(grid[y*DLUGOSC+x]);
            temp = std::clamp(temp, 0, 29999);
            WynikRGB kolor = mapa_temperatur[temp];
            
            USTAW_KOLOR(pixels, x,y,kolor.r,kolor.g,kolor.b);
        }
    }
}

void podgrzewanie_grida(std::vector<std::pair<int,int>>&idxy,std::vector<float>&  grid_A,std::vector<float>&  grid_B,float moc,float promien){
    int r = static_cast<int>(promien);
    for (const auto pos:idxy){
        int mouse_x = pos.first;
        int mouse_y = pos.second;
        //std::cout<<mouse_x<<mouse_y;
        for (int dy = -r;dy<r+1;dy++){
            for (int dx= -r;dx <r+1;dx++){
                int x = mouse_x + dx;
                int y = mouse_y + dy;
                if (x>1 && x<DLUGOSC-1 && y>1 && y<DLUGOSC-1 ){
                    grid_A[y*DLUGOSC+x] += moc;
                    grid_B[y*DLUGOSC+x] += moc;


                }
            }
        }
    }
}
