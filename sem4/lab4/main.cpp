#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include "Matematyka.h"
#include<iostream>
#include<chrono>
#include<memory>
#include "Suwak.h"
#include<string>
#include <sstream>  // Do operacji na strumieniach tekstowych (stringstream)
#include <iomanip>  // Do manipulacji formatem (setprecision)
#include <barrier>
#include<algorithm>


// Zmienne współdzielone między wątkami
// Inicjalizujemy grid_render od razu wymiarami DLUGOSC x DLUGOSC wypełnionymi 0.0f














void Watek_Obliczanie(int watek,std::vector<float> &grid_A,std::vector<float>& grid_B,std::barrier<> & bariera,
        std::vector<std::pair<int,int>> &idx_do_kolorowania,
        std::mutex& idx_mutex,
        std::vector<float>& grid_render,
        std::mutex &grid_mutex,
        std::atomic<bool>& is_running,
        bool &nowa_klatka,
        std::atomic<float> &atomowa_moc,
        std::atomic<float> &atomowy_promien

        ) {
    // Tworzymy DWA bufory tylko raz, na początku życia wątku

    
            
    // Ustawianie warunków początkowych w obu buforach
    int start = watek*DLUGOSC/LICZBA_WATKOW;
    int koniec = start + DLUGOSC/LICZBA_WATKOW;

    if (start==0) start =1;
    if (koniec ==DLUGOSC) koniec =DLUGOSC -1;

    std::vector<float> bufor_roboczy;
    std::vector<std::pair<int,int>> idx_do_kolorowania_kopia;

    if (watek==0) bufor_roboczy.resize(DLUGOSC*DLUGOSC,0.0f);
    if (watek ==0 )
    {
        std::lock_guard<std::mutex> lock(grid_mutex);
        std::swap(grid_render, bufor_roboczy);
        nowa_klatka = true;
    }
    
    while (is_running) {
        if (watek==0){

            {
                std::lock_guard<std::mutex> lock(idx_mutex);
                std::swap(idx_do_kolorowania_kopia,idx_do_kolorowania);
                
            }
            
            podgrzewanie_grida(idx_do_kolorowania_kopia, grid_A, grid_B,
                atomowa_moc.load(), atomowy_promien.load());
            idx_do_kolorowania_kopia.clear();
        }


        // Przeliczamy symulację X razy między klatkami
        // Możesz teraz swobodnie dać tu nawet 100 iteracji, procesor tego nie poczuje!
        for(int i = 0; i < 50; i++) {
           
            // 1. Liczymy nowy stan na podstawie grid_A i zapisujemy do grid_B
            obliczenie_temp(grid_A, grid_B,start);
            
            // 2. Zamieniamy je rolami. std::swap po prostu podmienia 
            // ukryte wskaźniki wektorów bez przesuwania danych w RAM-ie.
            
        
            bariera.arrive_and_wait();
            if (watek==0)std::swap(grid_A, grid_B);
            bariera.arrive_and_wait();
        }

        if (watek==0)
        {
            bufor_roboczy = grid_A;
            {   
                // Przekazanie zaktualizowanej siatki (grid_A ma teraz najnowszy stan)
                std::lock_guard<std::mutex> lock(grid_mutex);
                std::swap(grid_render,bufor_roboczy);
                nowa_klatka = true;
            }
        }
        bariera.arrive_and_wait();
        // Niewielkie opóźnienie, aby rdzeń CPU mógł "odetchnąć"
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }


}


int main() {
    sf::Font czcionka;
    
    if (!czcionka.loadFromFile("arial.ttf")) { 
        std::cerr << "Błąd: Nie znaleziono pliku arial.ttf w folderze z programem!" << std::endl;
        // Warto przerwać działanie programu lub ustawić flagę błędu
        return -1; 
    }
    sf::Text napis_moc;
    napis_moc.setFont(czcionka);             // Przekazanie załadowanej czcionki
    napis_moc.setCharacterSize(10);          // Rozmiar czcionki w pikselach
    napis_moc.setFillColor(sf::Color::White); // Kolor liter
    // Opcjonalnie: czarny obrys, żeby tekst był czytelny na jasnym tle
    napis_moc.setOutlineColor(sf::Color::Black);
    napis_moc.setOutlineThickness(2.0f);
    napis_moc.setPosition(x_moc, 10.0f);     // Ustawienie pozycji (X, Y)

    sf::Text napis_promien;
    napis_promien.setFont(czcionka);             // Przekazanie załadowanej czcionki
    napis_promien.setCharacterSize(10);          // Rozmiar czcionki w pikselach
    napis_promien.setFillColor(sf::Color::White); // Kolor liter
    // Opcjonalnie: czarny obrys, żeby tekst był czytelny na jasnym tle
    napis_promien.setOutlineColor(sf::Color::Black);
    napis_promien.setOutlineThickness(2.0f);
    napis_promien.setPosition(x_promien, 10.0f); 

    Suwak pedzel_moc(x_moc, 30.0f, szerokosc, 20.0f, 1000.0f, 10000.0f, 5000.0f );
    Suwak pedzel_promien(x_promien, 30.0f, szerokosc, 20.0f, 1.0f, 20.0f, 5.0f );
    std::atomic<float> atomowa_moc{pedzel_moc.pobierz_wartosc()};
    std::atomic<float> atomowy_promien{pedzel_moc.pobierz_wartosc()};

    std::vector<float> grid_render_copy(DLUGOSC*DLUGOSC, 0.0f);   
    std::vector<float> grid_A(DLUGOSC*DLUGOSC, 0.0f);
    std::vector<float> grid_B(DLUGOSC*DLUGOSC, 0.0f); 

    std::barrier bariera(LICZBA_WATKOW);
    std::vector<std::pair<int,int>> idx_do_kolorowania;
    std::mutex idx_mutex;

    std::vector<float> grid_render(DLUGOSC*DLUGOSC, 0.0f);
    std::mutex grid_mutex;                       // Zabezpiecza grid_render
    std::atomic<bool> is_running{true};          // Flaga do bezpiecznego wyłączenia wątku
    bool nowa_klatka = false;



    bool rysuj_nowe = false;

    sf::RenderWindow window(sf::VideoMode(DLUGOSC,DLUGOSC), "Rozchodzenie ciepla");
    window.setFramerateLimit(60);
    

    std::vector<std::thread> watki;
    for (int i = 0; i<LICZBA_WATKOW;i++){
        watki.push_back(std::thread(Watek_Obliczanie,i,std::ref(grid_A), std::ref(grid_B),std::ref(bariera), 
        std::ref(idx_do_kolorowania),
        std::ref(idx_mutex),
        std::ref( grid_render),
        std::ref( grid_mutex),
        std::ref(is_running),
        std::ref(nowa_klatka),
        std::ref(atomowa_moc),
        std::ref(atomowy_promien)));
    }
    

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
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed ){
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::Backspace){
                    std::fill(grid_A.begin(), grid_A.end(), 0);
                    std::fill(grid_B.begin(), grid_B.end(), 0);

                }
            }
           
            pedzel_moc.sprawdzZdarzenia(event,window);
            pedzel_promien.sprawdzZdarzenia(event,window);
        }
        atomowa_moc.store(pedzel_moc.pobierz_wartosc());
        atomowy_promien.store(pedzel_promien.pobierz_wartosc());


      
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& !pedzel_moc.czy_ciagniety() &&!pedzel_promien.czy_ciagniety() ) {
        // Pobierz pozycję myszki względem okna
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            

            if (mousePos.x>0 && mousePos.x<DLUGOSC && mousePos.y>0 && mousePos.y<DLUGOSC){
                std::lock_guard<std::mutex> lock(idx_mutex);
                idx_do_kolorowania.push_back({mousePos.x,mousePos.y});
            
            }

    }
        rysuj_nowe = false;
        {
            std::lock_guard<std::mutex> lock(grid_mutex);
            if (nowa_klatka){
                std::swap(grid_render_copy,grid_render);
                rysuj_nowe = true;
                nowa_klatka = false;
            }
        }
        if (rysuj_nowe){
        zmiania_temp_na_rgb(grid_render_copy, pixels);
        texture.update(pixels.data());
    }
        // for (std::vector<float> v:grid_render_copy){
        //     for (float i :v){
        //         std::cout<<i;
        //     }
        //     std::cout<<std::endl;
        // }
        // std::cout<<std::endl;
        std::stringstream text_moc;
        std::stringstream text_promien;

        text_moc<<"Moc pedzla [K]: "
            <<std::fixed<<std::setprecision(0)<<pedzel_moc.pobierz_wartosc();
        text_promien<<"Promien pedzla [Pxl]: "
            <<std::fixed<<std::setprecision(0)<<pedzel_promien.pobierz_wartosc();
        napis_moc.setString(text_moc.str());
        napis_promien.setString(text_promien.str());

        window.clear();
        window.draw(sprite);
        pedzel_moc.rysuj(window);
        pedzel_promien.rysuj(window);
        window.draw(napis_moc);
        window.draw(napis_promien);

        window.display();
    }
    is_running = false; // Zatrzymanie pętli w worker_thread
    for (std::thread& watek:watki){
        if (watek.joinable()) watek.join();
    } // Czekanie na poprawne zamknięcie wątku obliczeniowego

    return 0;
}