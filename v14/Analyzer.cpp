#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
	TRandom3 *random_number=new TRandom3();
	TCanvas *canvas=new TCanvas("","",1600,900);
	TH1F *histogram_1;
	fit=new TF1("fit","[0]*exp(-x/[1])",0,700);
	fit->SetParameter(0,500);
	fit->FixParameter(1,100);
	double kk;
	gStyle->SetOptFit(1);
	if (fChain == 0) 
	   return;
	Long64_t nbytes = 0, nb = 0;
	for(int j=0;j<1000;j++)
	{
		histogram_1=new TH1F("h","h",200,0,700);
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
	//histogram_1->Draw();
	chi_square_histo->Draw();
	gStyle->SetOptFit(1);
	canvas->SaveAs("z1.pdf");
}

void Analyzer::p_value_scan()
{
	
	TRandom3 *random_number=new TRandom3();
	TH1F *histo;
	TCanvas *canvas=new TCanvas("","",1600,900);
	double m_H,sigma,chi_square;
	double N,p_value;
	int korak=0;
	TGraph *m_p_graph=new TGraph();
	TF1 *p_value_fit;
	p_value_fit=new TF1("fit","[0]*exp(-x/[1])",0,700);
	p_value_fit->SetParameter(0,500);
	p_value_fit->FixParameter(1,100);
	for(int j=10;j<690;j=j+5)
    {
		m_H=j*1.0;
		sigma=0.0236*m_H;
		N=-(m_H-190.)*(m_H-190.)+0.5;
		histo=new TH1F("s","s",200,0,700);
		for(int i =0;i<pow(10,4);i++)
		{
			int r = rand()%100;
			if(r<N)//signal
			{
				histo->Fill(random_number->Gaus(m_H,sigma));
			}
			else//pozadina
			{
				histo->Fill(random_number->Exp(100));
			}
		}
		histo->Fit(p_value_fit,"q","",m_H-10,m_H+10);
		chi_square=p_value_fit->GetChisquare();
		p_value=chi_square_histo->Integral(chi_square_histo->FindBin(chi_square),200)/chi_square_histo->Integral();
		m_p_graph->SetPoint(korak,m_H,p_value);
		korak++;
    }
	gPad->SetLogy();
	m_p_graph->SetMinimum(pow(10,-5));
	m_p_graph->Draw("APL");
	canvas->SaveAs("z2.pdf");		
}


