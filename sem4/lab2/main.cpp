#include <iostream> 

#include "dane_stat.h"
#include "rozklady.h"
int main(int argc, char* argv[]) {

    if (argc ==1){std::cout<<"nie podano plikow";return 0;}



    //tworzenie fabryki
    FabrykaRozkladow::rejestruj(&RozkladGaussa::kreator,"Gauss",RozkladGaussa::id);
    FabrykaRozkladow::rejestruj(&RozkladPoissona::kreator,"Gauss",RozkladPoissona::id);
    FabrykaRozkladow::rejestruj(&RozkladLorentza::kreator,"Gauss",RozkladLorentza::id);

    
    //dodawanie "pustych " plikow przez proxy
    std::vector <std::unique_ptr<Plik>> pliki;
    for (int i =1;i<argc;i++){
        pliki.push_back(std::make_unique<Plik_proxy>(argv[i]));
    }

  
    
    
    
    while (true){
        //wybierania nr pliku
        std::cout<<"wybierz numer pliku z listy"<<std::endl;
        for (int i =1;i<argc;i++){
            std::cout<<i<<". "<<argv[i]<<" "; 
        }
        std::cout<<std::endl<<"jezeli chcesz zakonczyc wpisz 0"<<std::endl;
        int wybor;
        std::cin>>wybor;
        if (wybor==0){break;}


        //sprawdzenie czy uzytkowanik wprowadzil ok liczbe
        if (wybor<1 || wybor >argc){
            std::cout<<"podano nie prawidlowa liczbe";continue;}


        //wybiernia nr rozkladu    

        std::cout<<"wybierz rodzaj rozkladu"<<std::endl<<"1. dla gaussa 2. dla Poissona 3. dla Lorentza"<<std::endl;
        std::cout<<"jezli chcesz zakonczyc wpisz 0"<<std::endl;
        int wybor_roz;
        std::cin>>wybor_roz;
        if (wybor_roz==0){break;}

        //spr czy jest ok 
        if (wybor<1 || wybor >3){
            std::cout<<"podano nie prawidlowa liczbe";continue;}





        //wgrywanie dancyh z proxy    
        std::vector<float> dane;
        dane = pliki[wybor-1] ->daj_dane();

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
    




    
    return 0;
}