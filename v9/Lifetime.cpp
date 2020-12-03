#define Lifetime_cxx
#include "Lifetime.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

//Max likelihood fit na histogram
void Lifetime::Loop()
{
	double t_sum=time_sum();
	//f-ja time_sum vraća optimalan broj binova 
	t_histo=new TH1F("Time","Time",tau_bin(),0,10);
	
	TCanvas *t_canvas;
	t_canvas= new TCanvas("t_canvas","t_canvas",1600,900);
	
	double tau=1.22850e+00;
	double A=2.86160e+02;
	
	t_canvas->Divide(3,1);
	gStyle->SetOptFit(1111);
	t_fit=new TF1("BW","[0]*(1/[1]*exp(-x/[1]))",0,10);//parametar 0 je tau (vrime poluživota)
	t_fit->SetParameter(0,1);
	t_fit->SetParameter(1,1);
	t_fit->SetParName(0,"A");
	t_fit->SetParName(1,"#tau");
	
	
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   N=nentries;

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
	  //analitički određena vrijednost tau za pdf je suma_t/nentries
      t_histo->Fill(t);
   }
   double sum_t=time_sum();
   cout<<"Analiticki odredena vrijednost vremena poluzivota je   "<<sum_t/nentries<<endl;
   t_canvas->cd(1);
   gPad->SetLeftMargin(0.18);
   t_histo->Fit(t_fit,"l");
   t_histo->SetTitle("Measured lifetime fit");
   t_histo->GetXaxis()->SetTitle("t [s]");
   t_histo->GetYaxis()->SetTitle("Events / 0.35 GeV");
   t_histo->Draw();
   //pogreška za ovu metodu dobivena je u "1.sigma.pdf"
   //sigma_1=sqrt(1/(N/tau*tau-2*suma_t/tau*tau*tau));
   
   //za t=1s (jedno mjerenje)
   t_canvas->cd(2);
   gPad->SetLeftMargin(0.18);
   //za t uvrštavamo jednu jedinu vrijednost t=1s u funkciju t_fit; ostalo je sve isto
   t_fit_one=new TF1("BW","[0]*(1/x)*exp(-[1]/x)",0,10);//parametar funkcije je tau (zato  pišemo x u nazivniku)
   t_fit_one->SetParameter(0,2.86160e+02);
   t_fit_one->SetParameter(1,1.22850e+00);
   t_fit_one->SetTitle("Likelihood function for one measured time t=1s");
   t_fit_one->GetXaxis()->SetTitle("#tau [s]");
   t_fit_one->GetYaxis()->SetTitle("L(1,#tau)");
   //maksimum funkcije
   tau_max=t_fit_one->GetMaximumX();
   t_fit_one->Draw();
   //pogreška za ovu metodu dobivena je u "2.sigma.pdf"
    //sigma_2=sqrt(tau*tau*tau/(tau-1));
	
	//-2lnL
	t_canvas->cd(3);
	gPad->SetLeftMargin(0.18);
	lnL=new TF1("lnL","2*[0]*log(x)+2*[1]/x",1.18, 1.3);//parametar funkcije je  tau (vrime poluživota); [0] i [1] su nentries i suma vremena (papiri izvedeno)
	lnL->SetParameter(0,nentries);
	lnL->SetParameter(1,t_sum);
	lnL->SetTitle("Log-Likelihood function");
	lnL->GetXaxis()->SetTitle("#tau [s]");
	lnL->GetYaxis()->SetTitle("-2lnL");
	//minimum funkcije
	tau_min=lnL->GetMinimumX();
	lnL->Draw();
	//pogreška za ovu metodu dobivena je u "3.sigma.pdf"

   t_canvas->SaveAs("Time histo.pdf");	
  
}

//funkcija koja određuje promjenu parametra tau ovisno o broju binova
int Lifetime::tau_bin()
{
	TGraph	*tau_bin_graph = new TGraph();
	//histogram na koji se fita ML
	TH1F *compare_histo;
	
	TCanvas *canvas;
	canvas= new TCanvas("canvas","canvas",1600,900);
	
	//funkcija koja se fita na histogram ovisno o broju binova
	tau_fit=new TF1("tauu_fit","[0]*(1/[1]*exp(-x/[1]))",0,10);//parametar 1 je tau (vrime poluživota)
	tau_fit->SetParameter(0,1);
	tau_fit->SetParameter(1,1);
	tau_fit->SetParName(0,"A");
	tau_fit->SetParName(1,"#tau");
	
	double diff=1,opt_bin;
	double SUMA=time_sum();
	//petlja kreće od 11 jer nema smisla da u rasponu 0,10 stavimo 10 binova 
	for(bin_number=11;bin_number<=120;bin_number++)//200 je odabran na temelju pokušaja; nakon 200 sve točke su relativno blizu 
	{
		//broj binova histograma je varijabilan
		compare_histo=new TH1F("T","T",bin_number,0,10);//ili ga rebinat u svakom koraku petlje
		if (fChain == 0) 
		{
			return 0;
		}
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
			compare_histo->Fill(t);
		}
		compare_histo->Fit(tau_fit,"l");
		cout<<bin_number<<"\t"<<tau_fit->GetParameter(1)-SUMA/nentries<<endl;
		if(abs(tau_fit->GetParameter(1)-SUMA/nentries)<=diff)
		{
			//najmanja razlika analitički određenog tau i tau iz fita0>najpovoljniji broj binova
			diff=abs(tau_fit->GetParameter(1)-SUMA/nentries);
			cout<<diff<<endl;
			opt_bin=bin_number;
		}
			//popunjavanje grafa  (element klase TGraph) željenim vrijednostima
		tau_bin_graph->SetPoint(bin_number,bin_number,tau_fit->GetParameter(1));		
	}
	//cout<<"Optimalan broj binova je \t"<<opt_bin<<endl;
	tau_bin_graph->SetMinimum(1.2);
	tau_bin_graph->SetMaximum(1.24);
	tau_bin_graph->SetTitle("#tau number of bins dependence");
	tau_bin_graph->GetXaxis()->SetTitle("Number of bins");
	tau_bin_graph->GetYaxis()->SetTitle("#tau");
	tau_bin_graph->Draw("AC*");
	canvas->SaveAs("Tau_vs_bin.pdf");
	
	return opt_bin;
}


//funkcija koja računa sumu svih vremena
//funkcija je potreba jer se i za određivanje optimalnog broja binova koristi suma_t
//na ovaj način moguće je pozivati tau_bin neovisno o Loop
double Lifetime::time_sum()
{
	double suma_t=0.0;
	if (fChain == 0) 
		{
			return 0;
		}
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
			suma_t=suma_t+t;
		}
		return suma_t;
}


