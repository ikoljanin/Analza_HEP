#include "Analysis.h"
using namespace std;

int main() 
{
    Analysis *A;
	A=new Analysis();
	A->PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");
	A->PlotHistogram("/home/public/data/qqZZ/ZZ4lAnalysis.root");
	A->BW_AND_Q_FIT();
	A->All_area_ML_fit();
    return 0;
}