#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
	TRandom3 *random_number=new TRandom3();
	TCanvas *canvas=new TCanvas("","",1600,900);
	double kk;
	gStyle->SetOptFit(1);
	
	if (fChain == 0) 
	   return;
   Long64_t nentries = fChain->GetEntriesFast();
    nentries =pow(10,5);
   Long64_t nbytes = 0, nb = 0;
   for(int j=0;j<1000;j++)
   {
	   TH1F *histogram_1=new TH1F("h","h",200,0,700);
		for(int i =0;i<pow(10,5);i++)
		{
			histogram_1->Fill(random_number->Exp(100));
		}
		for(int k=10;k<690;k+=5)//fit šeta u prozorima po 5 koraka koji su raspona 20 
		{
			kk=k*1.0;
			histogram_1->Fit(fit,"q","",kk-10,kk+10);
			chi_square_histo->Fill(fit->GetChisquare());
		}	
   }
   chi_square_histo->Draw();
   gStyle->SetOptFit(1);
   canvas->SaveAs("z1.pdf");
}

void Analyzer::p_value_scan()
{
	
	TRandom3 *random_number_signal,*random_number_back;
	TH1F *histo;
	TCanvas *canvas=new TCanvas("","",1600,900);
	random_number_back=new TRandom3();
	random_number_signal=new TRandom3();
	double m_H=100,sigma=0.0236*m_H;
	double N;
	for(int j=10;j<=690;j=j+5)
    {
		m_H=j*1.0;
		N=-(m_H-190.)*(m_H-190.)+0.5;
		histo=new TH1F("s","s",700,0,700);
		for(int i =0;i<pow(10,4);i++)
		{
			int r = rand()%100;
			if(r>N)//pozadina
			{
				histo->Fill(random_number_signal->Gaus(m_H,sigma));
				//cout<<1<<endl;
			}
			else if(r<N)//signal
			{
				histo->Fill(random_number_back->Exp(100));
				//cout<<N<<endl;
			}
		}
		histo->Fit(fit,"q","",m_H-10,m_H+10);
		chi_square_histo->Fill(fit->GetChisquare());
		cout<<fit->GetChisquare()<<endl;
    }
	chi_square_histo->Draw();
	canvas->SaveAs("z2.pdf");		
}


