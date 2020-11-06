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
	TH1F *pT_histo;
	TH1F *Eta_histo;
	TH1F *Phi_histo;
	TH1F *BDT_histo;
	
	pT_histo=new TH1F("LepPt","Decay created lepton transversal momentum",100,0,140);
	Eta_histo=new TH1F("LepEta","Decay created lepton pseudorapidity",100,-4,4);
	Phi_histo=new TH1F("LepPhi","Decay created lepton azimuthal angle",100,-4,4);
	BDT_histo=new TH1F("LepBDT","Decay created lepton BDT results",100,0,10);
	
	
	 if (fChain == 0) 
	 {
		 return;
	 }
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	double scal;
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
		scal=(xsec*1000*overallEventWeight*137)/counter->GetBinContent(40);
		// if (Cut(ientry) < 0) continue;
		/*# KREIRANJE HISTOGRAMA #*/
		//varijable se mogu pozivati originalnim imenima (imena brancheva) jer ih root file automatski roota
		pT_histo->Fill(LepPt->at(1),scal); //u zagrade funkcija prima čime se želi filovat graf (PROLAZAK KROZ SVE BRANCHEVE SVAKOG RASPADA; U HISTOGRAM SE UBACUJE SAMO PT1)
		Eta_histo->Fill(LepEta->at(1),scal);
		Phi_histo->Fill(LepPhi->at(1),scal);
		BDT_histo->Fill(LepBDT->at(1),scal);
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
	pT_histo->Draw("HISTO");//kreiranje histograma  //po defaultu pozivanje funkcije Draw traži zadnji canvas i na njega se crta
	//Postavljanje x i y osi histograma
	pT_histo->GetXaxis()->SetTitle("2nd lepton p_{T} [GeV/C]");
	pT_histo->GetXaxis()->SetLabelSize(0.04);
	pT_histo->GetYaxis()->SetTitle("Number of events");
	pT_histo->GetYaxis()->SetTitleOffset(1.5);
	pT_histo->GetYaxis()->SetLabelSize(0.04);
	//mijenjanje boje histograma
	pT_histo->SetLineColor(kGreen-2);
	pT_histo->SetFillColor(kGreen-2);
	//legenda
	TLegend* pT_histo_leg;
	pT_histo_leg = new TLegend(0.9,0.8,0.7,0.9);
	pT_histo_leg->AddEntry(pT_histo, " 2nd decay lepton p_{T}", "l");
	pT_histo_leg->SetTextSize(0.03);
	pT_histo_leg->Draw();
	
	//crtanje na gornjoj desnoj strani platna
	c1->cd(2);
	Eta_histo->Draw("HISTO");
	//Postavljanje x i y osi histograma
	Eta_histo->GetXaxis()->SetTitle("2nd lepton Eta");
	Eta_histo->GetXaxis()->SetLabelSize(0.04);
	Eta_histo->GetYaxis()->SetTitle("Number of events");
	Eta_histo->GetYaxis()->SetTitleOffset(1.5);
	Eta_histo->GetYaxis()->SetLabelSize(0.04);
	//mijenjanje boje histograma
	Eta_histo->SetLineColor(kGreen-2);
	Eta_histo->SetFillColor(kGreen-2);
	//legenda
	TLegend* Eta_histo_leg;
	Eta_histo_leg = new TLegend(0.9,0.8,0.5,0.9);
	Eta_histo_leg->AddEntry(Eta_histo, "2nd decay lepton pseudorapidity", "l");
	Eta_histo_leg->SetTextSize(0.03);
	Eta_histo_leg->Draw();
	
	//crtanje na donjoj lijevoj strani platna
	c1->cd(3);
	Phi_histo->Draw("HISTO");
	//Postavljanje x i y osi histograma
	Phi_histo->GetXaxis()->SetTitle("2nd lepton Phi");
	Phi_histo->GetXaxis()->SetLabelSize(0.04);
	Phi_histo->GetYaxis()->SetTitle("Number of events");
	Phi_histo->GetYaxis()->SetTitleOffset(1.5);
	Phi_histo->GetYaxis()->SetLabelSize(0.04);
	//mijenjanje boje histograma
	Phi_histo->SetLineColor(kGreen-2);
	Phi_histo->SetFillColor(kGreen-2);
	//legenda
	TLegend* Phi_histo_leg;
	Phi_histo_leg = new TLegend(0.9,0.8,0.6,0.9);
	Phi_histo_leg->AddEntry(Phi_histo, "2nd decay lepton azim. angle", "l");
	Phi_histo_leg->SetTextSize(0.03);
	Phi_histo_leg->Draw();
	
	//crtanje na donjoj desnoj strani platna
	c1->cd(4);
	BDT_histo->Draw("HISTO");
	//Postavljanje x i y osi histograma
	BDT_histo->GetXaxis()->SetTitle("2nd lepton BDT");
	BDT_histo->GetXaxis()->SetLabelSize(0.04);
	BDT_histo->GetYaxis()->SetTitle("Number of events");
	BDT_histo->GetYaxis()->SetTitleOffset(1.5);
	BDT_histo->GetYaxis()->SetLabelSize(0.03);
	//mijenjanje boje histograma
	BDT_histo->SetLineColor(kGreen-2);
	BDT_histo->SetFillColor(kGreen-2);
	//legenda
	TLegend* BDT_histo_leg;
	BDT_histo_leg = new TLegend(0.9,0.8,0.6,0.9);
	BDT_histo_leg->AddEntry(BDT_histo, "2nd decay lepton BDT", "l");
	BDT_histo_leg->SetTextSize(0.03);
	BDT_histo_leg->Draw();

	c1->SaveAs("Pt1.pdf");
}

//REKONSTRUKCIJA

void Analysis::Reconstruction()
{
	TH1F *Higgs_Histo;
	//bin širine 2 GeV...25 događaja u rasponu od 50 
	Higgs_Histo=new TH1F("Mass","Higgs mass",25,90,140);
	
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
	//težina svakog događaja (u svakom događaju imamo 4 leptona)
	double w;
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
		//HFillanje histograma dešava se unutra
		//izračunata težina koja se dodjeljuje fillanju svakog događaja
		w=(xsec*1000*overallEventWeight*137)/counter->GetBinContent(40);
		Higgs_Histo->Fill(Higgs->M(),w);
		
   }
   		Higgs_Histo->Draw("HISTO");
		Higgs_Histo->GetXaxis()->SetTitle("Higgs mass");
		Higgs_Histo->GetXaxis()->SetLabelSize(0.04);
		Higgs_Histo->GetYaxis()->SetTitle("Events /2GeV");
		Higgs_Histo->GetYaxis()->SetTitleOffset(1.5);
		Higgs_Histo->GetYaxis()->SetLabelSize(0.04);
		//mijenjanje boje histograma
		Higgs_Histo->SetLineColor(kRed-2);
		Higgs_Histo->SetFillColor(kRed-2);
		//legenda
		TLegend* Higgs_Histo_leg;
		Higgs_Histo_leg = new TLegend(0.1,0.75,0.5,0.9);
		Higgs_Histo_leg->AddEntry(Higgs_Histo, "Reconstructed Higgs", "l");
		//Higgs_Histo_leg->AddEntry((TObject*)0, "", "");
		Higgs_Histo_leg->AddEntry((TObject*)0, "Number of reconstructed Higgs boson = 226.475", "");
		//Higgs_Histo_leg->AddEntry((TObject*)0, "", "");
		Higgs_Histo_leg->SetTextSize(0.02);
		Higgs_Histo_leg->Draw();
		cc->SaveAs("Higgs_mass.pdf");
		cout<<Higgs_Histo->Integral()<<endl;
		//integral se računa preko rootove funkcije koja integrira histogram
	
}


