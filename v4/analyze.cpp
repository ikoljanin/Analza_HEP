#include <iostream>
#include <string>
#include<fstream>
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TApplication.h"
#include "Analyzer.h"
using namespace std;

int main() 
{
    Analyzer *A;
	//char filename[] = "rezultati.root";
	//remove(filename); // prije unosenja podataka iz datoteke izbrisem prethodne podatke
	FILE *fp = fopen("rezultati.txt","r");
	TFile *hfile = hfile = TFile::Open("rezultati.root","RECREATE");
    A->read_function();
    //A->Convert_to_root();
    
    return 0;
}