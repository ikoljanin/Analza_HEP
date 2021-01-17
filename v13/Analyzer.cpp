#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
	
	h_average=0;
   if (fChain == 0) 
	   return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
		  break;
      nb = fChain->GetEntry(jentry);   
	  nbytes += nb;
	  h_average=h_average+height;//prosječna izmjerena visina
   }
   h_average=h_average/nentries;
   
}

void Analyzer::Test()
{
	h[0]=new TH1F("s","s",100,160,180);
	h[1]=new TH1F("f","f",100,160,180);
	h[2]=new TH1F("i","i",100,160,180);
	h[3]=new TH1F("n","n",100,160,180);
	TCanvas *canvas[3];
	gStyle->SetOptStat(0000);
	
	TLegend *legend_1,*legend_2,*legend_3;
	legend_1 = new TLegend(0.7,0.7,0.9,0.9);
	legend_2 = new TLegend(0.7,0.7,0.9,0.9);
	legend_3 = new TLegend(0.7,0.7,0.9,0.9);
	TLine *line;
	
	canvas[2]= new TCanvas("","",1600,900);
	canvas[3]= new TCanvas("","",1600,900);
	//gStyle->SetOptStat(0000);
	double mean=168.0,sigma=7.0; 
	double average,z_score,P_france,P_italy,P_netherland;
	TRandom *random_number;
	random_number=new TRandom();
	//početna hipoteza....španjolska
	for(int j=0;j<pow(10,6);j++)
	{
		average=0;
		for(int i=0;i<100;i++)
		{
			average=average+random_number->Gaus(mean,sigma);//generiranje podataka po gausu... 100 mjerenja napravljenih 10^6 x 
		}
		average=average/100;
		h[0]->Fill(average);
	}
	h[0]->Scale(1./h[0]->Integral());
	int bin = h[0]->FindBin(h_average);
	int last_bin=100;
	double P_spain= h[0]->Integral(0,bin);
	line = new TLine(h_average, 0, h_average, h[0]->Interpolate(average));
	line->SetLineColor(kBlue);
	//z_score = TMath::Sqrt(2)*TMath::ErfcInverse(2*P);
	//cout<<P<<"	"<<z_score<<endl;
	
	//alternativna hipoteza....francuska
	mean=164.7,sigma=7.1; 
	for(int j=0;j<pow(10,6);j++)
	{
		average=0;
		for(int i=0;i<100;i++)
		{
			average=average+random_number->Gaus(mean,sigma);//generiranje 10^6 pseudoeksperimenata za alternativnu hipotezu
		}
		average=average/100;
		h[1]->Fill(average);
	}
	h[1]->Scale(1./h[1]->Integral());
	bin = h[1]->FindBin(h_average);
	P_france= h[1]->Integral(bin,last_bin);
	cout<<"Francuska s eodbacuje s "<<(1-P_france/P_spain)*100<<" %"<<endl;
	
	//alternativna hipoteza....italija
	mean=166.1,sigma=6.5;
	for(int j=0;j<pow(10,6);j++)
	{
		average=0;
		for(int i=0;i<100;i++)
		{
			average=average+random_number->Gaus(mean,sigma);
		}
		average=average/100;
		h[2]->Fill(average);
	}
	h[2]->Scale(1./h[2]->Integral());
	bin = h[2]->FindBin(h_average);
	P_italy= h[2]->Integral(bin,last_bin);
	cout<<"Italija s eodbacuje s "<<(1-P_italy/P_spain)*100<<" %"<<endl;
	//cout<<P<<"	"<<z_score<<endl;
	
	
	//alternativna hipoteza....nizozemska
	mean=170.3,sigma=7.5;
	for(int j=0;j<pow(10,6);j++)
	{
		average=0;
		for(int i=0;i<100;i++)
		{
			average=average+random_number->Gaus(mean,sigma);
		}
		average=average/100;
		h[3]->Fill(average);
	}
	h[3]->Scale(1./h[3]->Integral());
	bin = h[3]->FindBin(h_average);
	P_netherland= h[3]->Integral(0,bin);
	cout<<"Nizozemska s eodbacuje s "<<(1-P_netherland/P_spain)*100<<" %"<<endl;
	//cout<<P<<"	"<<z_score<<endl;
	
	canvas[1]= new TCanvas("","",1600,900);
		h[0]->SetLineColor(kGreen);
		h[0]->SetFillColor(kGreen);
		h[1]->SetLineColor(kRed);
		h[1]->SetFillColor(kRed);
		legend_1->AddEntry(h[0], "Spain");
		legend_1->AddEntry(h[1], "France");
		legend_1->SetTextSize(0.03);
		h[0]->Draw("HISTO");
		h[1]->Draw("histo same");
		legend_1->Draw();
		line->Draw();
		canvas[1]->SaveAs("Spain_France.pdf");
		
	canvas[2]= new TCanvas("","",1600,900);
		h[0]->SetLineColor(kGreen);
		h[0]->SetFillColor(kGreen);
		h[2]->SetLineColor(kRed);
		h[2]->SetFillColor(kRed);
		legend_2->AddEntry(h[0], "Spain");
		legend_2->AddEntry(h[2], "Italy");
		legend_2->SetTextSize(0.03);
		h[0]->Draw("HISTO");
		h[2]->Draw("histo same");
		legend_2->Draw();
		line->Draw();
		canvas[2]->SaveAs("Spain_Italy.pdf");
	
	canvas[3]= new TCanvas("","",1600,900);
		h[0]->SetLineColor(kGreen);
		h[0]->SetFillColor(kGreen);
		h[3]->SetLineColor(kRed);
		h[3]->SetFillColor(kRed);
		legend_3->AddEntry(h[0], "Spain");
		legend_3->AddEntry(h[3], "Netherland");
		legend_3->SetTextSize(0.03);
		h[0]->Draw("HISTO");
		h[3]->Draw("histo same");
		legend_3->Draw();
		line->Draw();
		canvas[3]->SaveAs("Spain_Netherland.pdf");
	
}


