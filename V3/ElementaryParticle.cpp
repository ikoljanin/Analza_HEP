#include"ElementaryParticle.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <cstdlib>

     //##pozivanje konstruktora klase :: određuje kojoj klasi konstruktor pripada
    ElementaryParticle::ElementaryParticle (double x, string y, bool z)
    {
        masa_class=x;
        ime_class=y;
        boson_class=z;
    }

    void ElementaryParticle::print()//poivanje funkcije za ispis
    {
         cout << "Masa cestice "<<ime_class<<" je = " << masa_class << " ova cestica je bozon = "<< boson_class<< endl;

    }
    
    //funkcija za unos podataka i računanje energije Higgsa
    // pokH->...ovakvo pozivanje funkcije pamti poziciju px_class itd. i zna da je to za Higgsa
    double ElementaryParticle::Higgs_fourvector(double px, double py, double pz) 
    {
        px_class=px;
        py_class=py;
        pz_class=pz;
        E_class=sqrt(px_class*px_class+py_class*py_class+pz_class*pz_class+masa_class*masa_class);
    }

    //##funkcija za unos i računanje energije čestica na koje se raspadne ulazna čestica  
    double ElementaryParticle::vrijednost() //f-ja ne prima ništa jer sve šta koristi je globalno definirano
    {
        E_class=sqrt(px_class*px_class+py_class*py_class+pz_class*pz_class+masa_class*masa_class);
        return E_class;
    }

    //##funkcija za transverzanu količinu gibanja
    double ElementaryParticle::trans()
    {
        pt_class=sqrt(px_class*px_class+py_class*py_class);
        cout<<ime_class << pt_class <<endl;
    }

    //##definicija override konstruktora (korisno za pozivanje čestica na koje se raspada ulazna čestica)
    ElementaryParticle::ElementaryParticle()
    {
        masa_class=0;
        ime_class="";
        boson_class=false;    
    }

    //##funkcija raspada ulazne čestice na dvije nove
    void ElementaryParticle::bosonDecay(int c,ElementaryParticle *c1, ElementaryParticle *c2)
    {
        if(boson_class==false)
        {
            cout<<"Rapad nije moguć"<<endl;
        }

        else if(boson_class==true)//dogodi se raspad
        {
            int r = rand()%1000;
            //cout<< r <<endl;
            if(0<r && r<214)//raspad na 2 W bozon
            {
                c1->masa_class=80.38;
                c2->masa_class=80.38;
                c1->ime_class="W ";
                c2->ime_class="anti W";
                //četverovektor prve čestice raspada
                c1->px_class=(rand()%100)*(1.0)/100*px_class;
                c1->py_class=(rand()%100)*(1.0)/100*py_class;
                c1->pz_class=(rand()%100)*(1.0)/100*pz_class;
                c1->vrijednost();
                //četverovektor druge čestice raspada
                c2->px_class=px_class-c1->px_class;
                c2->py_class=py_class-c1->py_class;
                c2->pz_class=pz_class-c1->pz_class;
                c2->vrijednost();
            }
            else if(214<r && r<278)//raspad na 2 tau lepton
            {
                c1->masa_class=1.776;
                c2->masa_class=1.776;
                c1->ime_class="T ";
                c2->ime_class="anti T";
                //četverovektor prve čestice raspada
                c1->px_class=(rand()%100)*(1.0)/100*px_class;
                c1->py_class=(rand()%100)*(1.0)/100*py_class;
                c1->pz_class=(rand()%100)*(1.0)/100*pz_class;
                c1->vrijednost();
                //četverovektor druge čestice raspada
                c2->px_class=px_class-c1->px_class;
                c2->py_class=py_class-c1->py_class;
                c2->pz_class=pz_class-c1->pz_class;
                c2->vrijednost();

            }
            else if(278<r && r<304)//raspad na 2 Z bozon
            {  
                c1->masa_class=91.19;
                c2->masa_class=91.19;
                c1->ime_class="Z ";
                c2->ime_class="anti Z";
                //četverovektor prve čestice raspada
                c1->px_class=(rand()%100)*(1.0)/100*px_class;
                c1->py_class=(rand()%100)*(1.0)/100*py_class;
                c1->pz_class=(rand()%100)*(1.0)/100*pz_class;
                c1->vrijednost();
                //četverovektor druge čestice raspada
                c2->px_class=px_class-c1->px_class;
                c2->py_class=py_class-c1->py_class;
                c2->pz_class=pz_class-c1->pz_class;
                c2->vrijednost();
            }
            else if(r>304)//raspad na 2 b kvarkove
            {
                c1->masa_class=4.18;
                c2->masa_class=4.18;
                c1->ime_class="b";
                c2->ime_class="anti b";
                //četverovektor prve čestice raspada
                c1->px_class=(rand()%100)*(1.0)/100*px_class;
                c1->py_class=(rand()%100)*(1.0)/100*py_class;
                c1->pz_class=(rand()%100)*(1.0)/100*pz_class;
                c1->vrijednost();
                //četverovektor druge čestice raspada
                c2->px_class=px_class-c1->px_class;
                c2->py_class=py_class-c1->py_class;
                c2->pz_class=pz_class-c1->pz_class;
                c2->vrijednost();   
            }
            //cout<<c<<"  "<< ime_class<<"  "<< px_class<<" "<<py_class<<" "<<pz_class<<" "<<E_class<<endl; 
            //cout<<c<<"\t"<< c1->ime_class<<"\t"<<  c1->px_class<<"\t"<<c1->py_class<<"\t"<<c1->pz_class<<"\t"<<c1->E_class<<endl;  
            //cout<<c<<"\t"<< c2->ime_class<<"\t"<<  c2->px_class<<"\t"<<c2->py_class<<"\t"<<c2->pz_class<<"\t"<<c2->E_class<<endl;
            ofstream file;
            file.open ("rezultati.txt",ios_base::app); //svaki put dodajem podatke u analysis.txt pa stavim app (append) jer inace izbrise podatke za prethodni Higgsov bozon
            file <<c<<"\t"<< c1->ime_class<<"\t"<<  c1->px_class<<"\t"<<c1->py_class<<"\t"<<c1->pz_class<<"\t"<<c1->E_class<<endl;
            file <<c<<"\t"<< c2->ime_class<<"\t"<<  c2->px_class<<"\t"<<c2->py_class<<"\t"<<c2->pz_class<<"\t"<<c2->E_class<<endl;
            file.close(); 

        }

    }


    

