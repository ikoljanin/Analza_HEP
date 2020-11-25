#define Analysis_cxx
#include "Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
using namespace std;

/*#######################################
#	KREIRANJE HISTOGRAMA IZ INPUT FILE #
########################################*/

void Analysis::PlotHistogram(TString input_file)//funkcija prima root file iz kojeg se učitava
{
	
	
	TFile *f;
	f = new TFile(input_file);//dio koji modificira funkciju tako da funkcija prima neki string koji govori koji root file otvaram
	 TDirectory * dir = (TDirectory*)f->Get(input_file+":/ZZTree");
	dir->GetObject("candTree",tree);
	Init(tree);
	counter = (TH1F*)f->Get("ZZTree/Counters");	//KOJI HISTOGRAM UČITAVAMO
	//čestice raspada Higgsa kao elementi klase TLorentzVecotr
	TLorentzVector *L[4];//polje pokazivača
	TString a;
	for(int i=1;i<=4;i++)
	{
		 //leptoni raspada
		L[i]=new TLorentzVector();
	}
	//z bozoni raspada
	TLorentzVector *Z1,*Z2;
	//Higgs
	TLorentzVector *Higgs;
	
	Z1=new TLorentzVector();
	Z2=new TLorentzVector();
	Higgs=new TLorentzVector();
	
	 if (fChain == 0) 
	 {
		 return;
	 }
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	double scal;//težina
	/*###########################################
	#	UCITAVANJE PODATAKA ZA DECAY LEPTONE #
	###########################################*/
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) 
		{
			break;
		}
		nb = fChain->GetEntry(jentry); 
		nbytes += nb;
		//Težina za svaki događaj
		scal=(xsec*1000*overallEventWeight*137)/counter->GetBinContent(40);
		
		for(int i=1;i<=4;i++)
		{
			/*#POSTAVLJANJE ČETVEROVEKTORA LEPTONA#*/
			L[i]->SetPtEtaPhiM(LepPt->at(i-1),LepEta->at(i-1),LepPhi->at(i-1),i-1);
		}
		*Z1=*L[1]+*L[2];
		
		*Z2=*L[3]+*L[4];
		//REKONSTRUKCIJA HIGGSA IZ LEPTONA I BOZONA
		*Higgs=*Z1+*Z2;
		//FILLANJE histograma signala i pozadine (ovisno o učitanom fileu)
		if(input_file=="/home/public/data/ggH125/ZZ4lAnalysis.root")
		{
			//Histogram rekonstruirane mase (signal)
			Signal_histo->Fill(Higgs->M(),scal);//Ako su učitani podatci signala puni se ovaj histogram
		}
		else //if(input_file=="/home/public/data/qqZZ/ZZ4lAnalysis.root")
		{
			Back_histo->Fill(Higgs->M(),scal);//ako su učitani pozadinski podatci puni se ovaj histogram
		}	
	}	
}

/*#######################################################
#	FUNKCIJA KOJA STACKA HISTO ZA POZADINU I SIGNAL	#
#######################################################*/

void Analysis::Reconstruction_plot()
{
		
		TCanvas *combined_canvas;
		combined_canvas	=	new TCanvas("c_c","c_c",1600,900);
		//konstruktor za spajanje histograma pozadine i siganala rekonstrukcije
		THStack *Higgs_Histo	=	new THStack();
		//dodavanje histograma za addanje
		Higgs_Histo->Add(Back_histo);
		Higgs_Histo->Add(Signal_histo);
		
		Higgs_Histo->Draw("HISTO");
		
		Signal_histo->SetLineColor(kRed);
		Back_histo->SetLineColor(kBlue);
		//setiranje legende i osi
		Higgs_Histo->GetXaxis()->SetTitle("mass / GeV");
		Higgs_Histo->GetYaxis()->SetTitle("Events/2 GeV");
		TLegend *Higgs_legend = new TLegend(0.9,0.7,0.5,0.9);  //x1,y1,x2,y2 are the coordinates of the Legend
		Higgs_legend->SetHeader("Reconstructed Higgs bosons", "C"); //C for centering
		Higgs_legend->AddEntry(Signal_histo,"Fusion signal ");
		Higgs_legend->AddEntry(Back_histo, "Background");
		Higgs_legend->Draw();
		combined_canvas->SaveAs("Higgs_mass_histo.pdf");
	
		
}

/*##############################################
# F-JA ZA PLOTANJE KINEMATIČKOG DISKRIMINATORA #
###############################################*/
void Analysis::Reconstruction_plot_KD()
{
		TCanvas *combined_canvas_KD;
		combined_canvas_KD=	new TCanvas("cc","cc",1800,1000);
		combined_canvas_KD->Divide(2,2);
		//normalizacija na 1 (dobia kad san gugla normalizaciju histograma)
		combined_canvas_KD->cd(1);
		Signal_histo_KD->Scale(1/Signal_histo_KD->Integral());
		Back_histo_KD->Scale(1/Back_histo_KD->Integral());
		//crtanje kinematičkog diskriminatora za pozadinu i signal na istom platnu
		Signal_histo_KD->Draw("HISTO");
		Back_histo_KD->Draw("HISTO SAME");
		//
		Signal_histo_KD->SetLineColor(kRed);
		Signal_histo_KD->SetLineWidth(1.5);
		Back_histo->SetLineColor(kBlue);
		Back_histo_KD->SetLineWidth(1.5);
		//setiranje legende i osi
		Signal_histo_KD->GetXaxis()->SetTitle("Discrimin");
		Signal_histo_KD->GetYaxis()->SetTitle("Events/0.1");
		TLegend *disc_leg = new TLegend(0.4,0.8,0.6,0.9);  //x1,y1,x2,y2 are the coordinates of the Legend
		disc_leg->AddEntry(Signal_histo_KD,"Fusion signal");
		disc_leg->AddEntry(Back_histo_KD, "Background");
		disc_leg->Draw();
		
		combined_canvas_KD->cd(2);
		/*###########################
		#	kreiranje ROC krivulje  #
		###########################*/
		TGraph	*ROC_graph = new TGraph();
		/*for( i=1;i<=10;i++)
		{MOJ NAČIN NE VALJA
			x[i]=(Back_histo_KD->Integral(i,1));
			y[i]=(Signal_histo_KD->Integral(i,1));
			//gledamo sve događaje manje od 0.3 (to su binoi 0-0.1, 0.1-0.2 i 0.2-0.3 ili objedinjeno 0-0.3.....zato integral ide od 1(prvi bin) do 3 (treći bin)  
		}*/
		for(int i=1;i<=10;i++)
		{
			x[i]=1-Back_histo_KD->Integral(1,i);
			y[i]=1-Signal_histo_KD->Integral(1,i);
			ROC_graph->SetPoint(int(i),x[i],y[i]);
		}
		ROC_graph->SetMinimum(0.95);
		ROC_graph->SetMaximum(1.0);
		ROC_graph->GetXaxis()->SetTitle("Background efficiency");
		ROC_graph->GetYaxis()->SetTitle("Signal efficiency");
		ROC_graph->Draw("ap");
		
		combined_canvas_KD->cd(3);
		signal2d_histo->Draw("colz");
		
		combined_canvas_KD->cd(4);
		back2d_histo->Draw("colz");
		
		combined_canvas_KD->SaveAs("Higgs_mass_histo_KD.pdf");	
}

/*###########################################################
#	FUNKCIJA KOJA FITA BW I Q NA ZBROJ SIGNALA I POZADINE	#
###########################################################*/
void Analysis::BW_AND_Q_FIT()
{
	TH1F *back_and_signal_histo;
	back_and_signal_histo=new TH1F("","",50,70,170);
	TF1 *BW,*Q,*BW_AND_Q;
	BW=new TF1("BW","([0]*[1])/((x*x-[2]*[2])*(x*x-[2]*[2])+0.25*[1]*[1])",110,150);
	Q=new TF1("Q","[0]+[1]*x+[2]*x*x",110,150);
	BW_AND_Q=new TF1("BWQ","([0]*[1])/((x*x-[2]*[2])*(x*x-[2]*[2])+0.25*[1]*[1])+[3]+[4]*x+[5]*x*x",110,150);
	//prikazivanje svih parametara fita
	gStyle->SetOptFit(1111);
	//preimenovanje parametara za prikaz na grafu
	BW_AND_Q->SetParName(0,"D");
	BW_AND_Q->SetParName(1,"#Gamma");
	BW_AND_Q->SetParName(2,"M");
	BW_AND_Q->SetParName(3,"C");
	BW_AND_Q->SetParName(4,"B");
	BW_AND_Q->SetParName(5,"A");

	TCanvas *BW_Q_canvas;
	BW_Q_canvas= new TCanvas("c1","c1",1600,900);
	BW_Q_canvas->Divide(2,1);
	
	BW_Q_canvas->cd(1);
	//PARAMETRI točno određeni nakon fita
	BW->SetParameters(2.18998e+04,9.58079e+02 ,1.24918e+02);
	Q->SetParameters(8.23026e+01,-1.13951e+00 ,4.57065e-03);
	
	BW_AND_Q->SetParameter(0,2.18998e+04);
	BW_AND_Q->SetParameter(1,9.58079e+02);
	BW_AND_Q->SetParameter(2,1.24918e+02);
	BW_AND_Q->SetParameter(3,8.23026e+01 );
	BW_AND_Q->SetParameter(4,-1.13951e+00);
	BW_AND_Q->SetParameter(5, 4.57065e-03 );
	
	BW_AND_Q->SetLineColor(kBlue);
	Q->SetLineColor(kGreen);
	BW->SetTitle("BW, Q and BW+Q");
	BW->SetMaximum(110);
	BW->GetXaxis()->SetTitle("Mass / GeV");
	BW->Draw();
	Q->Draw("SAME");
	BW_AND_Q->Draw("SAME");
	
	BW_Q_canvas->cd(2);
	//postavljanje željenog područja za fit uaznih histograma
	Signal_histo->GetXaxis()->SetRangeUser(110.0,150.0);
	Back_histo->GetXaxis()->SetRangeUser(110.0,150.0);
	back_and_signal_histo->GetXaxis()->SetRangeUser(110.0,150.0);
	//zbrajanje histograma signala i pozadine  na željenom području 
	back_and_signal_histo->Add(Signal_histo);
	back_and_signal_histo->Add(Back_histo);
	//fit modela na zbroj histograma pozadine i signala
	back_and_signal_histo->Fit(BW_AND_Q);
	back_and_signal_histo->SetTitle("BW+Q fit");
	back_and_signal_histo->GetXaxis()->SetTitle("Mass / GeV");
	back_and_signal_histo->Draw("PE1X0");
	
	BW_Q_canvas->SaveAs("BW_Q_FIT_110_150GeV.pdf");
}

/*###################################################################
#	FUNKCIJA KOJA FITA MAX LIK METODOM NA CIJELO PODRUČJE PODATAKA	#
###################################################################*/
//fit se radi na cijeo područje 
void Analysis::All_area_ML_fit()
{
	TCanvas *ml_canvas;
	ml_canvas= new TCanvas("c_1","c_1",1600,900);
	gStyle->SetOptFit(1111);
	
	TH1F *back_and_signal_histo_ML; //mora se definirat novi TH1F element za addanje jer ako se koristi onaj od prije zezne se sve
	back_and_signal_histo_ML=new TH1F("","",50,70,170);
	
	TF1 *BW_signal_ml,*BW_back_ml,*Q_ml,*BW_AND_Q_ml;//zbog dva peaka postoje BW za signal i za pozadinu 
	
	BW_signal_ml=new TF1("BW_s","([0]*[1])/((x*x-[2]*[2])*(x*x-[2]*[2])+0.25*[1]*[1])",70,170);//BW za signali dio
	BW_back_ml=new TF1("BW_b","([0]*[1])/((x*x-[2]*[2])*(x*x-[2]*[2])+0.25*[1]*[1])",70,170);//BW za pozadinski dio
	Q_ml=new TF1("Q","[0]+[1]*x+[2]*x*x",70,170);
	BW_AND_Q_ml=new TF1("BWQ","([0]*[1])/((x*x-[2]*[2])*(x*x-[2]*[2])+0.25*[1]*[1])+([3]+[4]*x+[5]*x*x)+([6]*[7])/((x*x-[8]*[8])*(x*x-[8]*[8])+0.25*[7]*[7])",70,170);
	//preimenovanje parametara za prikaz na grafu
	BW_AND_Q_ml->SetParName(0,"D_{signal}");
	BW_AND_Q_ml->SetParName(1,"#Gamma_{signal}");
	BW_AND_Q_ml->SetParName(2,"M_{signal}");
	BW_AND_Q_ml->SetParName(3,"C");
	BW_AND_Q_ml->SetParName(4,"B");
	BW_AND_Q_ml->SetParName(5,"A");
	BW_AND_Q_ml->SetParName(6,"D_{background}");
	BW_AND_Q_ml->SetParName(7,"#Gamma_{background}");
	BW_AND_Q_ml->SetParName(8,"M_{background}");
	//setiranje parametara
	BW_signal_ml->SetParameters(2.04150e+04,8.29916e+02,1.24443e+02);
	BW_back_ml->SetParameters(4.27919e+04,8.90531e+02,9.08734e+01);
	Q_ml->SetParameters(5.18016e+01,-6.21281e-01,2.45073e-03);
	BW_AND_Q_ml->SetParameter(0,2.04150e+04);
	BW_AND_Q_ml->SetParameter(1,8.29916e+02);
	BW_AND_Q_ml->SetParameter(2,1.24443e+02);
	BW_AND_Q_ml->SetParameter(3,5.18016e+01);
	BW_AND_Q_ml->SetParameter(4,-6.21281e-01);
	BW_AND_Q_ml->SetParameter(5, 2.45073e-03);
	BW_AND_Q_ml->SetParameter(6,4.27919e+04);
	BW_AND_Q_ml->SetParameter(7,8.90531e+02);
	BW_AND_Q_ml->SetParameter(8,9.08734e+01);
	
	//postavljanje željenog područja za fit ulaznih histograma
	Signal_histo->GetXaxis()->SetRangeUser(70.0,170.0);
	Back_histo->GetXaxis()->SetRangeUser(70.0,170.0);
	back_and_signal_histo_ML->GetXaxis()->SetRangeUser(70.0,170.0);
	
	back_and_signal_histo_ML->Add(Signal_histo);
	back_and_signal_histo_ML->Add(Back_histo);
	//fit modela na zbroj histograma pozadine i signala
	back_and_signal_histo_ML->Fit(BW_AND_Q_ml,"L");//L naznači da se fit radi po max lik. metodi
	back_and_signal_histo_ML->SetTitle("BW+Q fit");
	back_and_signal_histo_ML->GetXaxis()->SetTitle("Mass / GeV");
	back_and_signal_histo_ML->Draw("PE1X0");
	
	ml_canvas->SaveAs("BW_Q_FIT_70_170GeV.pdf");	
}



