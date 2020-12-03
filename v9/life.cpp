#include "Lifetime.h"
using namespace std;

int main() 
{
    Lifetime *A;
	A=new Lifetime();
	A->Loop();
	//A->tau_bin();
    return 0;
}