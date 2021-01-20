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
	chi_square_histo->Scale(1./chi_square_histo->Integral());//globalni histogram
	chi_square_histo->Draw();
	gStyle->SetOptFit(1);
	canvas->SaveAs("z1.pdf");
}

void Analyzer::inv_mass()
{
	
	TCanvas *canvas=new TCanvas("","",1600,900);
	TF1 *inv_mass_fit;
	inv_mass_fit=new TF1("fit","[0]*exp(-x/[1])",0,700);
	inv_mass_fit->SetParameter(0,500);
	inv_mass_fit->FixParameter(1,100);
	TLorentzVector *f1,*f2;
	f1=new TLorentzVector();
	f2=new TLorentzVector();

	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) 
		{
			break;
		}
		nb = fChain->GetEntry(jentry); 
		nbytes += nb;
		f1->SetPxPyPzE(particle1_px,particle1_py,particle1_pz,particle1_E);
		f2->SetPxPyPzE(particle2_px,particle2_py,particle2_pz,particle2_E);
		*Higgs=*f1+*f2;
		inv_mass_histo->Fill(Higgs->M());
   }
   inv_mass_histo->Fit(inv_mass_fit);
   inv_mass_histo->Scale(1./inv_mass_histo->Integral());
   inv_mass_histo->Draw("EP");
   canvas->SaveAs("inv_mass.pdf");
}

void Analyzer::p_value_scan()
{
	TRandom3 *random_number=new TRandom3();
	TRandom3 *r=new TRandom3();
	TH1F *histo;
	TCanvas *canvas=new TCanvas("","",1600,900);
	double m_H,sigma,chi_square;
	double N,p_value_expected,p_value_observed;
	int korak=0;
	TGraph *Expected_p_value_graph=new TGraph();//očekivana vrijednost za p
	TGraph *observer_p_value_graph=new TGraph();//izmjerena vrijednost za p
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
			if(r->Rndm()<N)//signal
			{
				histo->Fill(random_number->Gaus(m_H,sigma));
			}
			else//pozadina
			{
				histo->Fill(random_number->Exp(100));
			}
		}
		histo->Fit(p_value_fit,"q","",m_H-10,m_H+10);//fitanje teorije na simulirane podatke
		chi_square=p_value_fit->GetChisquare();
		p_value_expected=chi_square_histo->Integral(chi_square_histo->FindBin(chi_square),200);//p vrijednost za simulirane podatke
		Expected_p_value_graph->SetPoint(korak,m_H,p_value_expected);
		
		inv_mass_histo->Fit(p_value_fit,"q","",m_H-10,m_H+10);//fitanje teorije na izmjerene podatke
		chi_square=p_value_fit->GetChisquare();//određivanje chi square vrijednosti
		p_value_observed=chi_square_histo->Integral(chi_square_histo->FindBin(chi_square),140);//izračunavanje p vrijednosti za observed podatke
		observer_p_value_graph->SetPoint(korak,m_H,p_value_observed);
		korak++;
    }
	TMultiGraph *mg = new TMultiGraph();
	gPad->SetLogy();
	Expected_p_value_graph->SetLineColor(kRed);
	observer_p_value_graph->SetLineColor(kBlue);
	mg->Add(Expected_p_value_graph);
	mg->Add(observer_p_value_graph);
	//Expected_p_value->SetMinimum(pow(10,-5));
	mg->Draw("AL");
	canvas->SaveAs("p_value.pdf");		
}



