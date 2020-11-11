#include "Analysis.h"
using namespace std;

int main() 
{
    Analysis *A;
	A=new Analysis();
	A->PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");
	A->PlotHistogram("/home/public/data/qqZZ/ZZ4lAnalysis.root");
	A->Reconstruction_plot();
	A->Reconstruction_plot_KD();
    return 0;
}