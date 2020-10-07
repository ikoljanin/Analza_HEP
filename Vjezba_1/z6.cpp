#include <iostream>
using namespace std;

// create a class
class EP
{
    public: //javne varijable klase; SVOJSTVA OBJEKATA TE KLASE 
        double masa_class;
        string ime_class;
        bool boson_class;
    //definicija konstruktora klase 
    EP (double x, string y, bool z) //konstruktor klase se zove isto kao i sama klasa
    {
        masa_class=x;
        ime_class=y;
        boson_class=z;
    }
    void print()//funkcija za ispis
    {
         cout << "Masa cestice "<<ime_class<<" je = " << masa_class << " ova cestica je bozon = "<< boson_class<< endl;
        
    }
    
};

int main() 
{
    double masa=11.1;
    string ime="Z bozon";
    bool boson=true;
    //pokazivač na Z
     EP *pokZ; 
    //definicija objekta klase preko pokazivača; new kaže "kreiraj novi objekt na poziciji tog pokazivača preko zadanog konstruktora"
    pokZ=new EP(masa,ime,boson);
    //definicija običnih objekata klase
    EP H(12,"Higgs",true);
    EP t(1,"Top kvark",false);
    //pozivanje funkcije za ispis
    pokZ->print();
    H.print();
    t.print();
    delete pokZ;

    return 0;
}
