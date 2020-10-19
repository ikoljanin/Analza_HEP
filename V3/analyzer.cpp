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
    double p_x;
    double p_y;
    double p_z;
    //pokazivač na objekt klase 
    ElementaryParticle *pokH;
    ElementaryParticle *decay_particle1;
    ElementaryParticle *decay_particle2;
    decay_particle1 = new ElementaryParticle(); 
    decay_particle2 = new ElementaryParticle();
    for(int i=1;i<=10000;i++) 
    {
        pokH=new ElementaryParticle(125.18,"Higgs",true);
        // korisnik određuje četverovektor higgsa
        p_x=-100+(100-(-100))*(rand()%1000)/1000;
        p_y=-100+(100-(-100))*(rand()%1000)/1000;
        p_z=-100+(100-(-100))*(rand()%1000)/1000;
        //elementi četverovektora Higgsa definirani su preko funkcije
        pokH->Higgs_fourvector(p_x,p_y,p_z); 
        //funkcija šalje objekte klase (pokazivač na objekte); funkciju poziva poznata čestica; ulazni su "prazne čestice"
        pokH->bosonDecay(i,decay_particle1,decay_particle2);
        delete pokH;   
    }
    delete decay_particle1;
    delete decay_particle2;
    return 0;
}



