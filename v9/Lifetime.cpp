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
	int bin_n=tau_bin();
	t_histo=new TH1F("Time","Time",bin_n,0,10);//f-ja tau_bin dat će optimalan broj binova
	
	TCanvas *t_canvas;
	t_canvas= new TCanvas("t_canvas","t_canvas",1600,900);
	
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
   cout<<"Analiticki odredena vrijednost vremena poluzivota je "<<sum_t/nentries<<"  , a  optimalan broj binova iznosi "<<bin_n<<endl;
   t_canvas->cd(1);
   gPad->SetLeftMargin(0.18);
   t_histo->Fit(t_fit,"l");
   t_histo->SetTitle("Measured lifetime fit");
   t_histo->GetXaxis()->SetTitle("t [s]");
   t_histo->GetYaxis()->SetTitle("Events / 0.28 s");
   t_histo->Draw();
   //pogreška za ovu metodu dobivena je dvostrukim deriviranjem lnL
   sigma_1= sqrt(-pow(t_fit->GetParameter(1),3)/(nentries*t_fit->GetParameter(1) - 2*sum_t));//analitička pogreška
   sigma_1_fit=t_fit->GetParError(1);//određivanje pogreške direktno iz roota
   
   //za t=1s (jedno mjerenje)
   t_canvas->cd(2);
   gPad->SetLeftMargin(0.18);
   //za t uvrštavamo jednu jedinu vrijednost t=1s u funkciju t_fit; ostalo je sve isto
   t_fit_one=new TF1("BW","[0]*(1/x)*exp(-[1]/x)",0,10);//parametar funkcije je tau (zato  pišemo x u nazivniku)
   t_fit_one->SetParameter(0,t_fit->GetParameter(0));
   t_fit_one->SetParameter(1,t_fit->GetParameter(1));
   t_fit_one->SetTitle("Likelihood function for one measured time t=1s");
   t_fit_one->GetXaxis()->SetTitle("#tau [s]");
   t_fit_one->GetYaxis()->SetTitle("L(1,#tau)");
   //maksimum funkcije
   tau_max=t_fit_one->GetMaximumX();
   t_fit_one->Draw();
	
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
	y_tau_min=lnL->GetMinimum();//funkcijska vrijednost za tau_min=x
	lnL->Draw();
	//pogreška za ovu metodu dobivena je kao preskej pravca -2lnL(tau_min)+1 s krivuljom -2lnL; zato je asimetrična greška (liva sigma_2; desna sigma_3)
	sigma_2=tau_min-lnL->GetX(y_tau_min+1,1,tau_min);
	//lnL->GetX(y_tau_min+1,0,tau_min); izbaci x za funkcijsku vrijednost y_tau_min+1, ali livo (presjek pravca y=y_tau_min+1 i krivulje -2lnL, livo od tau_min
	sigma_3=lnL->GetX(y_tau_min+1,tau_min,2)-tau_min;
	cout<<"Optimalan broj binova je \t"<<bin_n<<endl;
	cout<<"Analiticka pogreska iznosi \t"<<sigma_1<<", a pogreska određena iz fita Max likelihood iznosi \t"<<sigma_1_fit<<", lijeva pogreska iz -2lnL -"<<sigma_2<<" desna pogreska iz -2lnL +"<<sigma_3<<endl;
	t_canvas->SaveAs("Time histo.pdf");	
	//cout<<Pogreška
  
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
			opt_bin=bin_number;//optimalan broj binova dobije se za najmanju raziku računalnog i analitičkog rješenja
		}
			//popunjavanje grafa  (element klase TGraph) željenim vrijednostima
		tau_bin_graph->SetPoint(bin_number,bin_number,tau_fit->GetParameter(1));		
	}
	
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


