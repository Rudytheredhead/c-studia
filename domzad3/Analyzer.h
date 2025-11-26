#ifndef ANALYZER_H
#define ANALYZER_H
#include <string>
#include <vector>
using namespace std;
class Analyzer{
private:
    vector<double> dane;
public:
    Analyzer();
    void load_from_file(string file);
    void print();



};

#endif