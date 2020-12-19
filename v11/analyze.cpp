#include "Analyzer.h"
using namespace std;

int main() 
{
	
    Analyzer *A;
	int x;
	//gornji i donji limit za primjer s predavanja
    //A->upper_limit_cp(1,4,0.6827);
	//A->lower_limit_cp(1,4,0.6827);
	//A->CP_for10(10,0.6827);//10 događaja conf- interval
	//A->dice_throw(0.6827);
	cout<<"Input r for display"<<endl;
	cin>>x;
	A->Draw_cp_zone(x,10,0.6827);
    
    return 0;
}