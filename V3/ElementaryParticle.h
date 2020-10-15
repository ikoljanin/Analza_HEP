#include <iostream>
using namespace std;

// create a class
class ElementaryParticle
{
    public: //javne varijable klase; SVOJSTVA OBJEKATA TE KLASE 
        double masa_class;
        string ime_class;
        bool boson_class;
        //elementi četverovektora 
        double px_class,py_class,pz_class,pt_class,E_class;
        
    //definicija konstruktora klase 
    ElementaryParticle (double x, string y, bool z,double px, double py, double pz); //konstruktor klase se zove isto kao i sama klasa; poziva se u cpp dijel; //; zbog pozivanja 

    //definicjla funkcije
    void print() ;//funkcija za ispis poziva se u cpp dijelu

    //funkcija za unos podataka i računanje energije
    double vrijednost();
    
    //funkcija za transverzalnu količinu gibanja
    double trans();
    
    //override konstruktora ElementaryParticle
    ElementaryParticle();//po zadatku ne prima ništa

    //bosonDecay funkcija
    void bosonDecay(ElementaryParticle *c1,ElementaryParticle *c2);
    
 
};




