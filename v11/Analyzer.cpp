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
double Analyzer::upper_limit_cp(int input_r,int input_N,double C) //funkcija prima broj eljenih realizacija, broj pokušaja i conf level
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
		}	
		if(input_r==input_N)//bitno za f-ju CP_for10
		{
			return 1;
		}
		if(suma_up>=((1-((1-C)/2))))//pogađamo p sve dok suma ne postane >= confidence intervalu
		{
			p_up=p_j;
			break;//kad suma zadovolji prekidamo petlju jer smo odredili za koji je to p_j=p+
		}	
		p_j=p_j+0.001;
	}	
	while(p_j<=1.0);
	
	return p_up;	
}

//donji limit (ideja analogna gornjem limitu)
double Analyzer::lower_limit_cp(int input_r,int input_N,double C)
{
	double p_j=1.0;
	double p_lw=0.0,suma_lw;
	do//na ovaj način "pogađamo" p-
	{
		suma_lw=0.0;
		for(int r_i=0;r_i<=input_r-1;r_i++)
		{
			suma_lw=suma_lw+Bin_Distr(r_i,p_j,input_N);	
		}	
		if(input_r==0)//bitno za f-ju CP_for10
		{
			return 0;//nemoguće da se ništa ne očekuje za realizaciju
		}
		if(suma_lw>=((1-((1-C)/2))))
		{
			p_lw=p_j;
			break;
		}	
		p_j=p_j-0.001;//spuštamo se od 1 do 0 i tražimo p-
	}	
	while(p_j<=1.0);
	
	return p_lw;	
}

//funkcija koja za neki broj realizacija od mogućih 10 događaja ispisuje conf. interval
void Analyzer::CP_for10(int input_N,double C)
{
	double upper_p,lower_p;
	//CP interval za 10 događaja
	for(int r=0;r<=input_N;r++)//petlja određuje broj očekivano izvršenih događaja od 10 mogućnosti
	{
		upper_p=upper_limit_cp(r,input_N,C);//upper limit za i željenih realizacija
		lower_p=lower_limit_cp(r,input_N,C);//lower limit za i željenih realizacija
		cout<<"Interval za "<<r<<" zeljenih realizacija od 10 dogadaja je \t ["<<lower_p<<","<<upper_p<<"]"<<endl;
	}
	return;	
}

//funkcija za bacanje kockice
void Analyzer::dice_throw(double C)//rima conf. limit ovisno je li jedan ili dva sigma
{
	srand((unsigned)time(0));
	double upper_limit,lower_limit;
	int pokrivenost=0;
	for(int j=0;j<1000;j++)//željei eksperiment 10 bacanja kockice ponavlja se 1000 puta
	{
		int result,counter=0;
		for(int i=0;i<10;i++)//deset bacanja kockice za svaki j-ti eksperiment
		{
			result=rand()%6+1;//generira random broj od 1 do 6...rand()%6 daje ostatke pri djeljenju sa 6 (0,1,2,3,4,5) pa zato +1...skripta UTB
			if(result==6)
			{
				counter++;//broji povoljne događaje u 10 bacanja kockice za svaki j-t eksperiment... counter = r
			}
		}
		upper_limit=upper_limit_cp(counter,10,C);//određuje p+ za r=counter okretanja broja 6 u 10 bacanja s vjerojatnošću 1 sigma
		lower_limit=lower_limit_cp(counter,10,C);
		//p_true je 1/6...to je prava vjerojatnost za reazizaciju broja broja 6
		if(upper_limit>=1/6 && lower_limit<=1/6)//1/6 je između p- i p+
		{
			pokrivenost++;//u koliko od 1000 eksperimenata je 1/6 u conf. intervalu
		}
	}
	cout<<pokrivenost<<endl;	
}

//funkcija za crtanje CP pojasa
void Analyzer::Draw_cp_zone(int input_N,double C)
{
	TCanvas *canvas;
	gStyle->SetOptStat(0000);
	canvas= new TCanvas("c1","c1",1600,900);
	
	THStack *CPzone = new THStack("CPzone","CPzone");
	
	TH1F *limit_up_histo,*limit_down_histo;
	limit_up_histo=new TH1F("Upper limit","Upper limit",input_N,0,input_N);//broj binova,početak, kraj
	limit_down_histo=new TH1F("CPZone","CPZone",input_N,0,input_N);
	
	for(int i=0;i<=input_N;i++)//prolazimo kroz sve moguće brojeve realizacija za 10 događaja i punimo histograme
	{
		limit_up_histo->SetBinContent(i,upper_limit_cp(i,input_N,C));// ne radi ovako....Fill(upper_limit_cp(i,input_N,C)); google kaže za egzaktne SetBinContent
		limit_down_histo->SetBinContent(i,lower_limit_cp(i,input_N,C));	
	}
	limit_down_histo->SetMaximum(1.0);
	limit_down_histo->SetMinimum(0.0);
	limit_up_histo->SetMaximum(1.0);
	limit_up_histo->SetMinimum(0.0); 
	limit_down_histo->GetXaxis()->SetTitle("N");
	limit_down_histo->GetYaxis()->SetTitle("p");
	limit_down_histo->Draw();
	limit_up_histo->Draw("same");
	canvas->SaveAs("CPZone.pdf");
}


