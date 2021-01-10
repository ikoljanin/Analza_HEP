#include "Analyzer.h"

int main () 
{
    Analyzer *A;
	A=new Analyzer();
	//A->Loop_b();
	//A->Loop_signal();
	//A->Plot_histogram();
	A->TMVATraining("BDT");
	A->plot("BDT");
	//A->TMVATraining("BDTG");
	//A->plot("BDTG");
	//A->TMVATraining("MLP");
	//A->plot("MLP");
	
	
	
	
    return 0;
}