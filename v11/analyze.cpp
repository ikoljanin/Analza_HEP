#include "Analyzer.h"
using namespace std;

int main() 
{
    Analyzer *A;
	//gornji i donji limit za primjer s predavanja
    //A->pu_cp(1,4,0.6827);
	//A->pl_cp(1,4,0.6827);

	A->CP_for10(10,0.6827);//10 događaja conf- interval
    
    return 0;
}