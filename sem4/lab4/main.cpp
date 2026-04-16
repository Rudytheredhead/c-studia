#include <iostream>
#include <vector>

double STALA = 1;
double Dt  = 0.1;
int DLUGOSC = 10;

void obliczenie_temp(std::vector<std::vector<float>>& plansza){
    std::vector<std::vector<int>>& plansza_kopia = plansza;
        for (int x = 0; x<DLUGOSC;x++){
            for(int y = 0; y<DLUGOSC;y++){
                double suma = 0.0;
                for (int dx = -1; dx<=1; dx++){
                    for (int dy = -1; dy<=1; dy++){
                        if  (dy == dx or dy == -dx){continue;}
                        if (x+dx <0 || x+dx >DLUGOSC-1 || y +dy <0 || y+dy >DLUGOSC-1){continue;}
                        suma+= plansza_kopia[x][y] - plansza_kopia[x+dx][y+dy];
            

                    }
                }
                plansza[x][y] += -STALA*Dt*suma;
    }}
};

int main(){
    std::vector<std::vector<int>> plansza(10, std::vector<int>(10,0));
    plansza[4][5] =500;
    for (int krok = 0; krok < 10;krok++){

        for (std::vector v:plansza){
            for (int liczba :v){
                std::cout<<liczba<<" ";
            }
            std::cout<<std::endl;
        }
        obliczenie_temp(plansza);
        std::cout<<std::endl<<"--------------------------------"<<std::endl;
    }
    return 0;

};