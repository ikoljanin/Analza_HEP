#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <Riostream.h>
#include <TColor.h>
#include <TLorentzVector.h>
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
# DODAVANJE FUNKCIJE ZA KREIRANJE HISTOGRAMA#
###########################################*/
void Analyzer::PlotHistogram()
{
	//deklaracija objekta klase histograma TH1F (DEFINIRAN U .H)
	Histo1=new TH1F("Transverzalna_1","Transverzalna_kolicina_gibanja",100,0,140);
	Histo2=new TH1F("Transverzalna_2","Transverzalna_kolicina_gibanja",100,0,140);
	Higgs_Histo=new TH1F("Transverzalna_2","Transverzalna_kolicina_gibanja",100,0,140);
	
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
	 //Histogram transverzalne količine gibanja Higgsa
	 Higgs_Histo->Fill(sqrt(Higgs->Px()*Higgs->Px()+Higgs->Py()*Higgs->Py()));
   }
   /*####################
   #	HISTOGRAM		#
   ####################*/
   //Objekt klase canvas je "platno" na koje se ucrtava histogram
	TCanvas *c1 ;
	c1= new TCanvas("c1","c1",800,1000);
	//po defaultu pozivanje funkcije Draw traži zadnji canvas i na njega se crta
   Histo1->Draw();//kreiranje histograma 
   c1->Update();
   //crtanje drugog histograma na istom "platnu"
   Histo2->Draw("same");
   //Postavljanje x i y osi histograma
   Histo1->GetXaxis()->SetTitle("X");
   Histo1->GetYaxis()->SetTitle("Y");

  
   //mijenjanje boje histograma
   Histo1->SetLineColor(kBlue);
   Histo1->SetFillColor(kBlue);
   
   //Histo1->SetFillStyle(kRed);
   //spremanje histograma u razlicite formate
   c1->SaveAs("Pt1.pdf");
   c1->SaveAs("Pt1.png");
   c1->SaveAs("Pt1.root");
   
   //c1-> Divide(1,2);//s...kako želimo podilit platno
   //c1->cd(nešto) di želimo na platnu doć, u koji dio
   
   /*##############
   #	LEGENDA*  #
   ##############*/
    /*  TLegend legend = new TLegend(0.1,0.7,0.48,0.9);
   legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
   legend->AddEntry(h1,"Histogram filled with random numbers","f");
   legend->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
   legend->AddEntry("gr","Graph with error bars","lep");
   legend->Draw();*/
   
	
	
}
//TLorentzVector je gotova klasa
//TLorentzVector *p1=new TLorentzVector(.....)
//p1->set(px,py,pz,E);
//TLorentzVector *p2=new TLorentzVector(elementi četverovektora)
//TLorentzVector *Higs=*p1+*p2 //zbrajanje cilog definiranog četverovektora
