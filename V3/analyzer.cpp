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
    for(int i=1;i<=10000;i++) 
    {
        //random generiranje elemenata količine gibanja Higgsovog bozona između -100 i 100
        p_x=-100+(100-(-100))*(rand()%1000)/1000;
        p_y=-100+(100-(-100))*(rand()%1000)/1000;
        p_z=-100+(100-(-100))*(rand()%1000)/1000;
        decay_particle1 = new ElementaryParticle(); 
        decay_particle2 = new ElementaryParticle();
        pokH=new ElementaryParticle(125.18,"Higgs",true,p_x,p_y,p_z);
        pokH->bosonDecay(i,decay_particle1,decay_particle2);//funkcija šalje objekte klase (pokazivač na objekte); funkciju poziva poznata čestica; ulazni su "prazne čestice"
        delete pokH;
        delete decay_particle1;
        delete decay_particle2;
    }
    return 0;
}

