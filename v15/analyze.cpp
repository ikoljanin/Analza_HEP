#include "Analyzer.h"

int main () 
{
    Analyzer *A;
	A=new Analyzer();
	A->Loop();
	A->inv_mass();
	A->p_value_scan();
    return 0;
}