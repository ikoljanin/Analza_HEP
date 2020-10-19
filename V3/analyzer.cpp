#include <iostream>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include"ElementaryParticle.h"
using namespace std;

int main() 
{
    srand(time(NULL));
    double masa=11.1;
    string ime="Z bozon";
    bool boson=true;    
    double p_x;
    double p_y;
    double p_z;
    //pokazivač na objekt klase
    ElementaryParticle *pokZ; 
    ElementaryParticle *pokH;
    ElementaryParticle *pokT;
    ElementaryParticle *decay_particle1;
    ElementaryParticle *decay_particle2;
    //definicija objekta klase preko pokazivača; new kaže "kreiraj novi objekt na poziciji tog pokazivača preko zadanog konstruktora"
    //pokZ=new ElementaryParticle(masa,ime,boson,p_x,p_y,p_z);
   // pokH=new ElementaryParticle(125.18,"Higgs",true,p_x,p_y,p_z);
    //pokT=new ElementaryParticle(1,"Top kvark",false,1,1,1);
    //čestice raspada definirane preko "praznog" konstruktora

    //pozivanje funkcije za računanje energije i unos količine gibanja
    //pokZ->vrijednost();
    //T->vrijednost();
    // H->vrijednost();
    decay_particle1 = new ElementaryParticle(); 
    decay_particle2 = new ElementaryParticle();
    for(int i=1;i<=10000;i++) 
    {
        pokH=new ElementaryParticle(125.18,"Higgs",true);
        //funkcija koja random generira komponente četverovektora Higgsa
        pokH->Higgs_fourvector();
        //funkcija šalje objekte klase (pokazivač na objekte); funkciju poziva poznata čestica; ulazni su "prazne čestice"
        pokH->bosonDecay(i,decay_particle1,decay_particle2);
        delete pokH;   
    }
    delete decay_particle1;
    delete decay_particle2;
    return 0;
}



