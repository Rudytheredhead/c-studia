#include "Analyzer.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>

Analyzer::Analyzer(){}
 void Analyzer::load_from_file(string file){
    ifstream plik_wejsciowy;
    
    plik_wejsciowy.open(file);
    if (plik_wejsciowy.is_open()){
        double liczba;
        while(plik_wejsciowy >> liczba){
            dane.push_back(liczba);
        }

    }else{
        cout<<"zla nazwa pliku"<<endl;
        return;
    }

 }
 void Analyzer::print(){
     for (int i = 0; i<dane.size();i++){
         cout<<dane[i]<<" ";

     }
     cout<<endl;
 }