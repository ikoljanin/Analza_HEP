#include <iostream>
#include <string>
#include<sstream>
#include <fstream>
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TApplication.h"
// create a class
class Analyzer
{

     public: 

    //definicija konstruktora klase 
    Analyzer (); //konstruktor klase se zove isto kao i sama klasa; poziva se u cpp dijelu

    //funkcija za učitavanje podataka iz .txt datoteke
    void read_function();

    //funkcija za konvertiranje u root file
    void Convert_to_root();
        
};