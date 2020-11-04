#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <Riostream.h>
#include <TColor.h>
#include <TLorentzVector.h>
#include <TLegend.h>
using namespace std;

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   // jentry 0 je svih 13 brancheva za 1. raspad, jentry 2 13 brancheva za 2. raspad etc.
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) 
		  break;
      nb = fChain->GetEntry(jentry); 
	  nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  //######MOJA DODAVANJA
	  //varijable se mogu pozivati originalnim imenima (imena brancheva) jer ih root file automatski roota
		cout<<*ime1_class;
   }
}

/*###########################################
# 	FUNKCIJA ZA KREIRANJE HISTOGRAMA		#
###########################################*/
void Analyzer::PlotHistogram()
{
	//deklaracija objekta klase histograma TH1F (DEFINIRAN U .H)
	Histo1=new TH1F("Transverzalna_1","Decay particles transversal momentum",100,0,140);
	Histo2=new TH1F("Transverzalna_2","Decay particles transversal momentum",100,0,140);
	Higgs_Histo=new TH1F("Transverzalna_2","Higgs transversal momentum",100,0,140);
	
	//čestice raspada Higgsa kao elementi klase TLorentzVecotr
	TLorentzVector *p1;//prva čestica raspada
	TLorentzVector *p2;//Druga čestica raspada
	TLorentzVector *Higgs;
	
	p1=new TLorentzVector();
	p2=new TLorentzVector();
	Higgs=new TLorentzVector();
	
	 if (fChain == 0) 
	 {
		 return;
	 }
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	//petlja po svim branchevima 
	// jentry 0 je svih 13 brancheva za 1. raspad, jentry 2 13 brancheva za 2. raspad etc.
	/*###########################################
	#	UCITAVANJE PODATAKKA ZA FILL HISTOGRAMA #
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
		// if (Cut(ientry) < 0) continue;
		/*# KREIRANJE HISTOGRAMA #*/
		//varijable se mogu pozivati originalnim imenima (imena brancheva) jer ih root file automatski roota
		Histo1->Fill(pt1_class); //u zagrade funkcija prima čime se želi filovat graf (PROLAZAK KROZ SVE BRANCHEVE SVAKOG RASPADA; U HISTOGRAM SE UBACUJE SAMO PT1)
		Histo2->Fill(pt2_class);//drugi histogram puni se podatcima za drugu česticu raspada
	  
		//za svaki branch učitava se za p1 i p2 potrebno za rekreiranje higgsa
		p1->SetPxPyPzE(px1_class,py1_class,pz1_class,E1_class);//funkcija koja postavlja četverovektor na željenu vrijednost
		p2->SetPxPyPzE(px2_class,py2_class,pz2_class,E2_class);
		//zbrojeni četverovektori
		*Higgs=*p1+*p2;
		//Histogram transverzalne količine gibanja Higgsa (fillanje se dešava u petlji)
		Higgs_Histo->Fill(Higgs->Pt());
   }
   /*####################
   #	HISTOGRAM		#
   ####################*/
   //Objekt klase canvas je "platno" na koje se ucrtava histogram
	TCanvas *c1 ;
	//uklanjanje default legende s platna (u zagradu ide nula onoliko koliko default doda u legendu članova)
	gStyle->SetOptStat(0);
	c1= new TCanvas("c1","c1",1600,900);
	
	//podjela platna na pola
	c1->Divide(2,1);

	//crtanje na lijevoj strani platna
	c1->cd(1);
	Histo1->Draw();//kreiranje histograma  //po defaultu pozivanje funkcije Draw traži zadnji canvas i na njega se crta
	//Postavljanje x i y osi histograma
	Histo1->GetXaxis()->SetTitle("Decay particle p_{T} [GeV/C]");
	Histo1->GetYaxis()->SetTitle("Number of events");
	//mijenjanje boje histograma
	Histo1->SetLineColor(kGreen);
	Histo1->SetFillColor(kGreen);
	c1->Update();
	//crtanje drugog histograma na istom "platnu"
	Histo2->Draw("same");
	Histo2->SetLineWidth(2);
	//dodavanje legende na livu stranu platna
	TLegend* leg1;
	leg1 = new TLegend(0.9,0.8,0.48,0.9);
	leg1->AddEntry(Histo1, "First decay particle p_{T}", "l");
	leg1->AddEntry(Histo2, "Secund decay particle p_{T}", "l");
	leg1->Draw();
	
	//crtanje na desnoj strani platna
	c1->cd(2);
    Higgs_Histo->Draw();
	Higgs_Histo->SetLineColor(kRed);
	Higgs_Histo->SetLineWidth(1.5);
	Higgs_Histo->GetXaxis()->SetTitle("Higgs pT [GeV/C]");
	Higgs_Histo->GetYaxis()->SetTitle("Number of events");
	//dodavanje legende na desnu stranu platna
	TLegend* leg2;
	leg2 = new TLegend(0.1,0.85,0.40,0.9);
	leg2->AddEntry(Higgs_Histo, "Higgs pT", "l");
	leg2->Draw();

	//spremanje histograma u razlicite formate
	c1->SaveAs("Pt1.pdf");
	c1->SaveAs("Pt1.png");
	c1->SaveAs("Pt1.root");	
}

