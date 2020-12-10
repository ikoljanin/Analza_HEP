#include <iostream>
#include <string>
#include<sstream>
#include <fstream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>
#include <THStack.h>
#include <TGraph.h>
#include <TF1.h>
#include <TStyle.h>
#include <TLatex.h>
#include <iostream>
#include <TFrame.h>
#include <TGraphErrors.h>
#include <TLine.h>
#include <TLatex.h>
using namespace std;
// create a class
class Analyzer
{

     public : 
	 //definicija konstruktora klase 
		Analyzer (); 
	
    //funkcija 
    void Least_Squares();
};