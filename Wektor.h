#ifndef WEKTOR_H
#define WEKTOR_H

#include <iostream>
#include<vector>
#include<string>

class Wektor{
private:
int N;
float *wspolrzedne;

public:
Wektor(int N=4);
Wektor(int N, const float* data);
Wektor(const Wektor& inny);
~Wektor();

float& operator[](int indeks);
Wektor operator+(const Wektor &inny) const;
Wektor operator-(const Wektor &inny) const;
Wektor& operator=(const Wektor &inny);


friend std::ostream& operator<<(std::ostream& os, const Wektor& wektor);

};


#endif