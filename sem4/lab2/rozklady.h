#ifndef ROZKLADY_H
#define ROZKLADY_H
#include<vector>
#include<string>
#include<map>
#include<memory>
//klasa glowna do rozkladow
class Rozklad{
    protected:

    float estymator_;
    std::string nazwa_;
    const std::vector<float>& dane_;
    public:

    Rozklad(const std::vector <float>& dane): dane_(dane){}
    virtual ~Rozklad() = default;
    float get_estymator();
    std::string get_nazwa();

};
typedef Rozklad*(*KreatorRozkladu)(const std::vector <float>&);

class RozkladGaussa:public Rozklad{
    public:
    RozkladGaussa(const std::vector <float>& dane);
    
    static Rozklad *kreator (const std::vector <float>& dane){
        return new RozkladGaussa(dane);
    }
    static const int id;
};

class RozkladPoissona:public Rozklad{
    public:
    RozkladPoissona(const std::vector <float>& dane);
    
    static Rozklad *kreator (const std::vector <float>& dane){
        return new RozkladPoissona(dane);
    }
    static const int id;
};

class RozkladLorentza:public Rozklad{
    public:
    RozkladLorentza(const std::vector <float>& dane);
    
    static Rozklad *kreator (const std::vector <float>& dane){
        return new RozkladLorentza(dane);
    }
    static const int id;
};

class FabrykaRozkladow{
    private:

    static std::map<int,KreatorRozkladu> rozklady;
    static std::map<int,std::string> nazwy;
    
    public:
    
    static void rejestruj (KreatorRozkladu kr,std::string nazwa,int i){
        rozklady[i] = kr;
        nazwy[i] = nazwa;
    }
    static std::unique_ptr<Rozklad> utworz(const int & id, const std::vector<float> &dane){
        return std::unique_ptr<Rozklad>( rozklady[id] (dane));
    }
};
#endif 