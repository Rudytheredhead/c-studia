#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <future>
#include <execution>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <thread>
#include <iomanip>
#include "Obliczanie.h"
void generate_data(std::vector<double>& data) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (double& val : data) {
        val = dist(gen);
    }
}


int main() {
    // Ustawienia testu
    const size_t NUM_ELEMENTS = 10'000'000; // 10 milionow
    const int NUM_TRIALS = 10;              // Min. 10 prob
    
    // Pobranie liczby rdzeni/watkow wirtualnych procesora
    unsigned int p = std::thread::hardware_concurrency();
    if (p == 0) p = 4; // Zabezpieczenie, jesli system nie zwroci wartosci

    // Otwarcie pliku do zapisu
    std::ofstream outfile("wyniki_wydajnosci.txt");
    if (!outfile.is_open()) {
        std::cerr << "Blad: Nie udalo sie utworzyc pliku wyniki_wydajnosci.txt!\n";
        return 0;
    }

    // Naglowek pliku i ekranu
    std::cout << "Test wydajnosci na " << p << " watkach.\nProsze czekac...\n";
    
    outfile << "=== Porownanie Wydajnosci Obliczen ===\n";
    outfile << "Rozmiar danych: " << NUM_ELEMENTS << " typu double\n";
    outfile << "Liczba watkow (p): " << p << "\n";
    outfile << "Ilosc prob: " << NUM_TRIALS << "\n\n";
    
    outfile << "Proba | Jednowatkowy [ms] | Wlasny Wielow. [ms] | STL Parallel [ms]\n";
    outfile << "---------------------------------------------------------------------\n";

    // Zmienne do usrednienia czasow
    double total_single = 0.0, total_multi = 0.0, total_stl = 0.0;
    
  
    


    std::vector<double> data(NUM_ELEMENTS);
    std::pair<double,double> final_res;
    for (int i = 1; i <= NUM_TRIALS; ++i) {
        std::cout << "Proba " << i << "/" << NUM_TRIALS << "... ";
        
        // Losowanie nowego zestawu
        generate_data(data);

        // 1. Pomiar - Jednowatkowy
        auto start = std::chrono::high_resolution_clock::now();
        final_res = liczenienie_jeden(data); 
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time_single = end - start;

        // 2. Pomiar - Wielowatkowy wlasny
        start = std::chrono::high_resolution_clock::now();
        final_res = licz_sam_podzial(data, p);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time_multi = end - start;

        // 3. Pomiar - Wielowatkowy STL
        start = std::chrono::high_resolution_clock::now();
        final_res = liczenie_auto(data);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time_stl = end - start;

        // Zapis wiersza do pliku
        outfile << std::setw(5) << i << " | "
                << std::setw(17) << std::fixed << std::setprecision(2) << time_single.count() << " | "
                << std::setw(19) << time_multi.count() << " | "
                << std::setw(17) << time_stl.count() << "\n";

        std::cout << "Zakonczono.\n";

        // Sumowanie do sredniej
        total_single += time_single.count();
        total_multi += time_multi.count();
        total_stl += time_stl.count();
    }

    // Obliczanie i zapis srednich do pliku
    outfile << "---------------------------------------------------------------------\n";
    outfile << "SREDN | "
            << std::setw(17) << std::fixed << std::setprecision(2) << (total_single / NUM_TRIALS) << " | "
            << std::setw(19) << (total_multi / NUM_TRIALS) << " | "
            << std::setw(17) << (total_stl / NUM_TRIALS) << "\n";

    outfile.close();
    
    // Wypisanie przykladowego wyniku, by optymalizator nie wyrzucil kodu
    std::cout << "\nTesty zakonczone sukcesem! Wyniki zostaly zapisane w pliku 'wyniki_wydajnosci.txt'.\n";
    std::cout << "(Ostatnie wyniki: "
              << "Srednia: " << final_res.first << ", Odchylenie: " << final_res.second << ")\n";

    return 0;
}