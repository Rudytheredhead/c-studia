#include "Analyzer.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;
int main(int argc, char **argv){
    if (argc != 4 || argc != 3){
        cout<<"nie prawidlowe dane przy wywolaniu programu";
        return 0;
    }
    Analyzer d;
    d.load_from_file(argv[2]);
    d.print();
    return 0;
}