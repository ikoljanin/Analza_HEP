#include <iostream>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include"ElementaryParticle.h"
using namespace std;

int main() 
{
    srand(time(NULL));
    double masa=11.1;
    string ime="Z bozon";
    bool boson=true;    
    double p_x=1.0;
    double p_y=1.0;
    double p_z=1.0;
    //pokazivač na Z
    ElementaryParticle *pokZ; 
    ElementaryParticle *pokH;
    ElementaryParticle *pokT;
    ElementaryParticle *decay_particle1;
    ElementaryParticle *decay_particle2;
    //definicija objekta klase preko pokazivača; new kaže "kreiraj novi objekt na poziciji tog pokazivača preko zadanog konstruktora"
    pokZ=new ElementaryParticle(masa,ime,boson,p_x,p_y,p_z);
    pokH=new ElementaryParticle(12,"Higgs",true,1,1,1);
    pokT=new ElementaryParticle(1,"Top kvark",false,1,1,1);
    //čestice raspada definirane preko "praznog" konstruktora
    decay_particle1 = new ElementaryParticle(); 
    decay_particle2 = new ElementaryParticle();
    //pozivanje funkcije za računanje energije i unos količine gibanja
    pokZ->vrijednost();
    //H->vrijednost();
    //T->vrijednost();
    pokZ->bosonDecay(decay_particle1,decay_particle2);//funkcija šalje objekte klase (pokazivač na objekte); funkciju poziva poznata čestica; ulazni su "prazne čestice"
    delete pokZ;
    delete pokH;
    delete pokT;
    //kreirajmo 10000 higsovih bozona i raspadnimo ih i zapišimo u txt file

    return 0;
}

