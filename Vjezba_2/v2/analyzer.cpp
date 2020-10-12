#include <iostream>
#include"ElementaryParticle.h"
using namespace std;

int main() 
{
    double masa=11.1;
    string ime="Z bozon";
    bool boson=true;
    //pokazivač na Z
    ElementaryParticle *pokZ; 
    //definicija objekta klase preko pokazivača; new kaže "kreiraj novi objekt na poziciji tog pokazivača preko zadanog konstruktora"
    pokZ=new ElementaryParticle(masa,ime,boson);
    ElementaryParticle H(12,"Higgs",true);
    ElementaryParticle t(1,"Top kvark",false);
    //pozivanje funkcije za ispis
    pokZ->print();
    H.print();
    t.print();
    delete pokZ;

    return 0;
}

