#ifndef A_h
#define A_h

class Wektor3D {
private:
    double x_, y_, z_;
public:
    Wektor3D(double x = 0, double y = 0, double z = 0);
    bool operator == (const Wektor3D& wektor) const;
    double operator * (const Wektor3D& wektor) const; 
    Wektor3D operator % (const Wektor3D& wektor) const;
    Wektor3D operator +(const Wektor3D& wektor) const;
    Wektor3D operator -(const Wektor3D& wektor) const;
    double modul() const;
    double modul2() const;
    double x() const;
    double y() const;
    double z() const;
    friend std::ostream& operator << (std::ostream& os, const Wektor3D& wektor);
    friend std::istream& operator >> (std::istream& is, Wektor3D& wektor);
    friend Wektor3D operator * (double scalar, const Wektor3D& wektor);
};

#endif
