#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include "Matematyka.h"
#include<iostream>

// Zmienne współdzielone między wątkami
std::vector<std::vector<float>>  grid_render; // Tylko do odczytu przez wątek rysujący
std::mutex grid_mutex;                       // Zabezpiecza grid_render
std::atomic<bool> is_running{true};          // Flaga do bezpiecznego wyłączenia wątku

//const int DLUGOSC = 800; //wielkosc pola
//warunki poczatkeowe
int srodek_x = 500;
int srodek_y = 500;
int promien = 50;





void Watek_Obliczanie(){
    std::vector<std::vector<float>> grid_calc(DLUGOSC, std::vector<float>(DLUGOSC, 0.0f));
    //ustawiania warunkoiw pocz
    for (int x = srodek_x-promien; x<srodek_x+promien;x++){
        for (int y = srodek_y-promien; y <srodek_y+promien;y++){
            grid_calc[x][y] = 20000.0f;
        }
    }
    {
        std::lock_guard<std::mutex> lock(grid_mutex);
        grid_render = grid_calc;
    }
    while (is_running){

        obliczenie_temp(grid_calc);
        {   //przekazywanie info do renderowania
            std::lock_guard<std::mutex> lock(grid_mutex);
            grid_render = grid_calc;
        }
    }

}

int main() {
    
    sf::RenderWindow window(sf::VideoMode(DLUGOSC,DLUGOSC), "Rozchodzenie ciepla");
    window.setFramerateLimit(60);
    std::thread worker_thread(Watek_Obliczanie);
    std::vector<std::vector<float>> grid_render_copy;

    // Tworzymy tablicę bajtów: szerokość * wysokość * 4 kolory (RGBA)
    // Używamy std::vector dla bezpiecznego zarządzania pamięcią
    std::vector<sf::Uint8> pixels(DLUGOSC * DLUGOSC * 4, 0); // Wypełnione zerami (czarny, w pełni przezroczysty)

   

    sf::Texture texture;
    texture.create(DLUGOSC,DLUGOSC);
    sf::Sprite sprite(texture);

    // Kopiujemy naszą tablicę bajtów bezpośrednio do tekstury
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        {
            std::lock_guard<std::mutex> lock(grid_mutex);
            grid_render_copy = grid_render;
        }

        zmiania_temp_na_rgb(grid_render_copy, pixels);
        texture.update(pixels.data());
        // for (std::vector<float> v:grid_render_copy){
        //     for (float i :v){
        //         std::cout<<i;
        //     }
        //     std::cout<<std::endl;
        // }
        // std::cout<<std::endl;

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}