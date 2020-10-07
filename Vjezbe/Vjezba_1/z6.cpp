#include <iostream>
using namespace std;

// create a class
class EP
{
    public: //javne varijable klase; SVOJSTVA OBJEKATA TE KLASE 
        double m;
        string ime;
        bool b;
    EP (double x, string y, bool z) //definicija konstruktora
    {
        m=x;
        ime=y;
        b=z;
    }
};


int main() 
{
    double masa=11.1;
    string im="Z bozon";
    bool bo=true;
    /*objekti klase EP
    EP H;
    EP t;

    // inicijalizacija svojstava objekata klase EP
    H.m = 96.5;
    t.m= 75.0; //funkcija objekta
  
    H.ime="Higgs";
    t.ime="Top kvark";

    H.b=true;
    t.b=false;

    cout << "Masa cestice " <<H.ime<< " je = " << H.m << "ova cestica je bozon = "<<H.b<< endl;
    cout << "Masa cestice "<<t.ime<<" je = " << t.m << " ova cestica je bozon = "<<t.b<< endl;*/

    EP Z(masa,im,bo);// inicijalizira se objekt klase preko konstruktora

    EP *pokZ; //pokazivač na Z
    cout << "Masa cestice "<<Z.ime<<" je = " << Z.m << " ova cestica je bozon = "<< Z.b<< endl;

    return 0;
}


