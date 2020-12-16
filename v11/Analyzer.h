#include <iostream>
#include <iomanip>
#include <math.h>
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
	double factoriel(int N);
    double Bin_Distr(int input_r,double input_p,int input_N);
	double pu_cp(int input_r,int input_N,double C);//gornja granica
	double pl_cp(int input_r,int input_N,double C);//donja granica
};