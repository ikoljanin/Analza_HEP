#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include<sstream>
#include <fstream>
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TApplication.h"
using namespace std;

// create a class
class PDFGenerator
{
	
    public: //javne varijable klase; SVOJSTVA OBJEKATA TE KLASE 
        double random_x;
		double random_y;
		double f_x;

    //definicija konstruktora klase 
    PDFGenerator (); 

    //definicja funkcije
    void GenerateQuadraticPDF() ;
	
	//potrebno za kreiranje histograma
	void Convert_to_root();
 
};

