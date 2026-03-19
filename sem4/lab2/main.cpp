#include <iostream> 
#include<stdexcept>
#include<algorithm>

#include "dane_stat.h"
#include "rozklady.h"
int main(int argc, char* argv[]) {

    if (argc ==1){std::cout<<"nie podano plikow";return 0;}



    //tworzenie fabryki
    FabrykaRozkladow::rejestruj(&RozkladGaussa::kreator,"Gauss",RozkladGaussa::id);
    FabrykaRozkladow::rejestruj(&RozkladPoissona::kreator,"Poisson",RozkladPoissona::id);
    FabrykaRozkladow::rejestruj(&RozkladLorentza::kreator,"Lorentz",RozkladLorentza::id);

    
    //dodawanie "pustych " plikow przez proxy
    std::vector <std::unique_ptr<Plik>> pliki;
    //sprawdzanie czy ktorys z plikow nie wywolal errora przy wgrywaniu i zapis do zle idx
    std::vector <int> zle_idx;
    for (int i =1;i<argc;i++){
        try{
            pliki.push_back(std::make_unique<Plik_proxy>(argv[i]));
        }catch(const std::runtime_error& error){
            std::cerr<<error.what()<<"plik "<<argv[i]<<" zostanie usuniety z listy plikow"<<std::endl;
            zle_idx.push_back(i);
        }
    }
    if (pliki.empty()){
        std::cout<<"nie podano zadnego prawidlowego pliku";
        return 0;
    }
    std::vector<std::string> argv_poprawka;
    for (int i =0;i<argc;i++){
        auto it = std::find(zle_idx.begin(), zle_idx.end(), i);
        if (it == zle_idx.end()){
            argv_poprawka.push_back(argv[i]);
        }
    }
    
    
    while (true){
        std::cout<<std::endl<<"-----------------------------"<<std::endl;

        //wybierania nr pliku
        std::cout<<"wybierz numer pliku z listy"<<std::endl;
        for (int i =1;i<argv_poprawka.size();i++){
            std::cout<<i<<". "<<argv_poprawka[i]<<" "; 
        }
        std::cout<<std::endl<<"jezeli chcesz zakonczyc wpisz 0"<<std::endl;
        int wybor;
        std::cin>>wybor;
        if (wybor==0){break;}

        //sprawdzenie czy uzytkowanik wprowadzil ok liczbe
        if (wybor<1 || wybor >argv_poprawka.size()-1){
            std::cout<<"podano nie prawidlowa liczbe";continue;}
 
        try{
            
            std::cout<<"wybrano plik "<< argv_poprawka[wybor]<<std::endl;
            std::cout<<"wybierz rodzaj rozkladu"<<std::endl<<"1. dla gaussa 2. dla Poissona 3. dla Lorentza"<<std::endl;
            std::cout<<"jezli chcesz zmienic wybor wpisz 0"<<std::endl;
            int wybor_roz;
            std::cin>>wybor_roz;
            if (wybor_roz==0){continue;}

            //spr czy jest ok 
            if (wybor_roz<1 || wybor_roz>3){
                std::cout<<"podano nie prawidlowa liczbe";continue;}
        
            const std::vector<float>& dane = pliki[wybor-1] ->daj_dane();
            //ustawinie par dla danego rozkladu    
            std::string operacja ;
            int numer_rozkladu;
            if(wybor_roz==1){ 
                operacja ="srednia";
                numer_rozkladu = RozkladGaussa::id;       
            }
            else if(wybor_roz==2){ 
                operacja ="srednia";
                numer_rozkladu = RozkladPoissona::id;       
            }
            else if(wybor_roz==3){ 
                operacja ="mediana";
                numer_rozkladu = RozkladLorentza::id;       
            }

            //liczenie i print

            std::unique_ptr<Rozklad>rozklad (FabrykaRozkladow::utworz(numer_rozkladu,dane));
            std::cout<<"estymator dla rozkladu "<<rozklad->get_nazwa()<<" ("<<operacja<<") wynosi "<<rozklad->get_estymator()<<std::endl;
            std::cout<<"-----------------------------"<<std::endl;
        }
        catch(const std::runtime_error& error){
            //program jak wylapie blad do go wypiesze przez strumien cerr i przejsdzie do kolejnej iteracji petli
            std::cerr<<error.what()<<std::endl;
            std::cout<<std::endl<<"-----------------------------"<<std::endl;
            continue;
        }
    }  
    return 0;
}