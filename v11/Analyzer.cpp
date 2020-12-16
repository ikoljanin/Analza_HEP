#include "Analyzer.h"
using namespace std; 

//konstruktor klase
Analyzer::Analyzer ()
{
       
}

//funkcija za računanje faktorjele
double Analyzer::factoriel(int N)
{
	int i=1;
	double factoriel_result=1.0;
	if(N==0)
	{
		factoriel_result=1;
	}
	else if(N!=0)
	{
		do
		{
			factoriel_result=factoriel_result*i;
			i++;
		}
		while(i<=N);
	}
	return factoriel_result;
}

//binomna f-ja
double Analyzer::Bin_Distr(int input_r,double input_p,int input_N)
{
	double f_N=factoriel(input_N);
	double f_r=factoriel(input_r);
	double f_Nr=factoriel(input_N-input_r);
	double brojnik=f_N*pow(input_p,input_r)*pow((1-input_p),(input_N-input_r));
	double binomial=brojnik/(f_r*f_Nr);
	return binomial;	
}

//gornji limit
double Analyzer::pu_cp(int input_r,int input_N,double C)
{
	double p_j=0.0;
	int k=0;
	double p_up=0.0,suma_up;
	do//na ovaj način "pogađamo" p+
	{
		suma_up=0.0;
		for(int r_i=input_r+1;r_i<=input_N;r_i++)
		{
			suma_up=suma_up+Bin_Distr(r_i,p_j,input_N);	
			//cout<<Bin_Distr(r_i,p_j,input_N)<<"\t"<<r_i<<"\t"<<p_j<<"\t"<<input_N<<endl;
		}	
		//cout<<p_j<<"\t"<<suma_up<<endl;
		if(suma_up>=((1-((1-C)/2))))//pogađamo p sve dok suma ne postane >= confidence intervalu
		{
			p_up=p_j;
			cout<<"Upper limit is \t"<<p_up<<endl;
			break;//kad suma zadovolji prekidamo petlju jer smo odredili za koji je to p_j=p+
		}	
		p_j=p_j+0.001;
	}	
	while(p_j<=1.0);;
	return p_up;	
}

//donji limit
double Analyzer::pl_cp(int input_r,int input_N,double C)
{
	double p_j=1.0;
	double p_lw=0.0,suma_lw;
	do//na ovaj način "pogađamo" p+
	{
		suma_lw=0.0;
		for(int r_i=0;r_i<=input_r-1;r_i++)
		{
			suma_lw=suma_lw+Bin_Distr(r_i,p_j,input_N);	
			//cout<<Bin_Distr(r_i,p_j,input_N)<<"\t"<<r_i<<"\t"<<p_j<<"\t"<<input_N<<endl;
		}	
		//cout<<p_j<<"\t"<<suma_up<<endl;
		if(suma_lw>=((1-((1-C)/2))))
		{
			p_lw=p_j;
			cout<<"Lower limit is \t"<<p_lw<<endl;
			break;
		}	
		p_j=p_j-0.001;//spuštamo se od 1 do 0 i tražimo p-
	}	
	while(p_j<=1.0);;
	return p_lw;	
	
}



