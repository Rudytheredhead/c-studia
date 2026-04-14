#include<memory>
#include<vector>
#include <algorithm>
#include <cmath>
#include"Obliczanie.h"
#include<iostream>

int main(){
     std::vector<double> test;
     test.push_back(1.0);
     test.push_back(2.0);
     std::pair<double,double> para = liczenie_auto(test);
     std::cout<<para.first<<para.second;

    return 0;
};