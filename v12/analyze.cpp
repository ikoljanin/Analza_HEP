#include "Analyzer.h"

int main () 
{
    Analyzer *A;
	A=new Analyzer();
	A->Loop_b();
	A->Loop_signal();
	A->Plot_histogram();
	//A->TMVATraining();
    return 0;
}