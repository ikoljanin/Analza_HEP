#include <iostream>
using namespace std;

// create a class
class ElementaryParticle
{
    public: //javne varijable klase; SVOJSTVA OBJEKATA TE KLASE 
        double masa_class;
        string ime_class;
        bool boson_class;

    //definicija konstruktora klase 
    ElementaryParticle (double x, string y, bool z); //konstruktor klase se zove isto kao i sama klasa; poziva se u cpp dijel; //; zbog pozivanja 

    //definicjla funkcije
    void print() ;//funkcija za ispis poziva se u cpp dijelu
 
};




