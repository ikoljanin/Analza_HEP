#define Analysis_cxx
#include "Analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include<iostream>
#include <Riostream.h>
#include <TColor.h>
#include <TLorentzVector.h>
#include <TLegend.h>
using namespace std;

void Analysis::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analysis.C
//      root> Analysis t
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
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	  //pristupanje vektoru tj. četvrtoj komponenti vektora (ide od 0 do 3 četiri komponente tj. 4 leptona)
	  cout<<LepPt->at(3)<<endl;
   }
}

//HISTOGRAM

void Analysis::PlotHistogram()
{
	//deklaracija objekta klase histograma TH1F (DEFINIRAN U .H)
	TH1F *Histo1;
	/*TH1F *Histo2;
	TH1F *Higgs_Histo;
	Histo1=new TH1F("LepPt","Lepton transversal momentum",100,0,140);
	Histo2=new TH1F("Transverzalna_2","Decay particles transversal momentum",100,0,140);
	Higgs_Histo=new TH1F("Transverzalna_2","Higgs transversal momentum",100,0,140);
	
	*/
	
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
		Histo1->Fill(LepPt->at(2)); //u zagrade funkcija prima čime se želi filovat graf (PROLAZAK KROZ SVE BRANCHEVE SVAKOG RASPADA; U HISTOGRAM SE UBACUJE SAMO PT1)
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
	c1->Divide(2,2);

	//crtanje na gornjoj lijevoj strani platna
	c1->cd(1);
	Histo1->Draw();//kreiranje histograma  //po defaultu pozivanje funkcije Draw traži zadnji canvas i na njega se crta
	//Postavljanje x i y osi histograma
	Histo1->GetXaxis()->SetTitle("Decay particle pT [GeV/C]");
	Histo1->GetYaxis()->SetTitle("Number of events");
	//mijenjanje boje histograma
	Histo1->SetLineColor(kGreen);
	Histo1->SetFillColor(kGreen);
	/*c1->Update();
	//crtanje drugog histograma na istom "platnu"
	Histo2->Draw("same");
	Histo2->SetLineWidth(2);
	//dodavanje legende na livu stranu platna
	TLegend* leg1;
	leg1 = new TLegend(0.9,0.8,0.48,0.9);
	leg1->AddEntry(Histo1, "First decay particle pT", "l");
	leg1->AddEntry(Histo2, "Secund decay particle pT", "l");
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
	
	c1->SaveAs("Pt1.png");
	c1->SaveAs("Pt1.root");	*/
	
	c1->SaveAs("Pt1.pdf");
}

//REKONSTRUKCIJA

void Analysis::Reconstruction()
{
	TH1F *Higgs_Histo;
	Higgs_Histo=new TH1F("Mass","Higgs mass",100,0,140);
	
	//čestice raspada Higgsa kao elementi klase TLorentzVecotr
	TLorentzVector *L1;//prva čestica raspada
	TLorentzVector *L2;//Druga čestica raspada
	TLorentzVector *L3;
	TLorentzVector *L4;
	TLorentzVector *Z1;
	TLorentzVector *Z2;
	TLorentzVector *Higgs;
	
	L1=new TLorentzVector();
	L2=new TLorentzVector();
	L3=new TLorentzVector();
	L4=new TLorentzVector();
	Z1=new TLorentzVector();
	Z2=new TLorentzVector();
	Higgs=new TLorentzVector();
	if (fChain == 0) 
	 {
		 return;
	 }
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	TCanvas *cc ;
		//uklanjanje default legende s platna (u zagradu ide nula onoliko koliko default doda u legendu članova)
		gStyle->SetOptStat(0);
		cc= new TCanvas("cc","cc",1600,900);
		Higgs_Histo->Draw();
	for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) 
		{
			break;
		}
		nb = fChain->GetEntry(jentry); 
		nbytes += nb;
		//za svaki branch učitava se za p1 i p2 potrebno za rekreiranje higgsa
		L1->SetPtEtaPhiM(LepPt->at(0),LepEta->at(0),LepPhi->at(0),0);//funkcija koja postavlja četverovektor na željenu vrijednost
		L2->SetPtEtaPhiM(LepPt->at(1),LepEta->at(1),LepPhi->at(1),0);
		*Z1=*L1+*L2;
		L3->SetPtEtaPhiM(LepPt->at(2),LepEta->at(2),LepPhi->at(2),0);//funkcija koja postavlja četverovektor na željenu vrijednost
		L4->SetPtEtaPhiM(LepPt->at(3),LepEta->at(3),LepPhi->at(3),0);
		*Z2=*L3+*L4;
		//zbrojeni četverovektori
		*Higgs=*Z1+*Z2;
		//HFillanje histograma dašava se unutra
		Higgs_Histo->Fill(Higgs->M());
		
   }
		cc->SaveAs("Higgs_mass.pdf");
   
	
}


