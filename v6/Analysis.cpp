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
	TH1F *pT1_histo,*pT2_histo,*pT3_histo,*pT4_histo;
	TH1F *Eta1_histo,*Eta2_histo,*Eta3_histo,*Eta4_histo;
	TH1F *Phi1_histo,*Phi2_histo,*Phi3_histo,*Phi4_histo;
	TH1F *BDT1_histo,*BDT2_histo,*BDT3_histo,*BDT4_histo;

	//širina bina=(početak-kraj)/broj binova ...(140-0)/50
	pT1_histo=new TH1F("LepPt1","Decay created lepton transversal momentum",50,0,140);//bin 2.8 GeV
	Eta1_histo=new TH1F("LepEta1","Decay created lepton pseudorapidity",80,-4,4);//bin 0.1
	Phi1_histo=new TH1F("LepPhi1","Decay created lepton azimuthal angle",80,-4,4);//bin 0.1 rad
	BDT1_histo=new TH1F("LepBDT1","Decay created lepton BDT results",30,0,10);//bin 0.33
	
	pT2_histo=new TH1F("LepPt2","Decay created lepton transversal momentum",50,0,140);
	Eta2_histo=new TH1F("LepEta2","Decay created lepton pseudorapidity",80,-4,4);
	Phi2_histo=new TH1F("LepPhi2","Decay created lepton azimuthal angle",80,-4,4);
	BDT2_histo=new TH1F("LepBDT2","Decay created lepton BDT results",30,0,10);
	
	pT3_histo=new TH1F("LepPt3","Decay created lepton transversal momentum",50,0,140);
	Eta3_histo=new TH1F("LepEta3","Decay created lepton pseudorapidity",80,-4,4);
	Phi3_histo=new TH1F("LepPhi3","Decay created lepton azimuthal angle",80,-4,4);
	BDT3_histo=new TH1F("LepBDT3","Decay created lepton BDT results",30,0,10);
	
	pT4_histo=new TH1F("LepPt4","Decay created lepton transversal momentum",50,0,140);
	Eta4_histo=new TH1F("LepEta4","Decay created lepton pseudorapidity",80,-4,4);
	Phi4_histo=new TH1F("LepPhi4","Decay created lepton azimuthal angle",80,-4,4);
	BDT4_histo=new TH1F("LepBDT4","Decay created lepton BDT results",30,0,10);
	
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
		pT1_histo->Fill(LepPt->at(0),scal); //u zagrade funkcija prima čime se želi filovat graf (PROLAZAK KROZ SVE BRANCHEVE SVAKOG RASPADA; U HISTOGRAM SE UBACUJE SAMO PT1)
		Eta1_histo->Fill(LepEta->at(0),scal);
		Phi1_histo->Fill(LepPhi->at(0),scal);
		BDT1_histo->Fill(LepBDT->at(0),scal);
		
		pT2_histo->Fill(LepPt->at(1),scal); //u zagrade funkcija prima čime se želi filovat graf (PROLAZAK KROZ SVE BRANCHEVE SVAKOG RASPADA; U HISTOGRAM SE UBACUJE SAMO PT1)
		Eta2_histo->Fill(LepEta->at(1),scal);
		Phi2_histo->Fill(LepPhi->at(1),scal);
		BDT2_histo->Fill(LepBDT->at(1),scal);
		
		pT3_histo->Fill(LepPt->at(2),scal); //u zagrade funkcija prima čime se želi filovat graf (PROLAZAK KROZ SVE BRANCHEVE SVAKOG RASPADA; U HISTOGRAM SE UBACUJE SAMO PT1)
		Eta3_histo->Fill(LepEta->at(2),scal);
		Phi3_histo->Fill(LepPhi->at(2),scal);
		BDT3_histo->Fill(LepBDT->at(2),scal);
		
		pT4_histo->Fill(LepPt->at(3),scal); //u zagrade funkcija prima čime se želi filovat graf (PROLAZAK KROZ SVE BRANCHEVE SVAKOG RASPADA; U HISTOGRAM SE UBACUJE SAMO PT1)
		Eta4_histo->Fill(LepEta->at(3),scal);
		Phi4_histo->Fill(LepPhi->at(3),scal);
		BDT4_histo->Fill(LepBDT->at(3),scal);
	}
   /*####################
   #	HISTOGRAM		#
   ####################*/
   //Objekt klase canvas je "platno" na koje se ucrtava histogram
	TCanvas *c1 ;
	//uklanjanje default legende s platna (u zagradu ide nula onoliko koliko default doda u legendu članova)
	gStyle->SetOptStat(0000);
	c1= new TCanvas("c1","c1",1600,900);
	
	//podjela platna na pola
	c1->Divide(2,2);

	//crtanje na gornjoj lijevoj strani platna
	c1->cd(1);
	pT1_histo->Draw("HISTO");//kreiranje histograma  //po defaultu pozivanje funkcije Draw traži zadnji canvas i na njega se crta
	//crtanje histograma ostalih četica na istom platnu
	pT2_histo->Draw("HISTO SAME");
	pT3_histo->Draw("HISTO SAME");
	pT4_histo->Draw("HISTO SAME");
	//Postavljanje x i y osi histograma
	pT1_histo->GetXaxis()->SetTitle("Decay epton p_{T} [GeV]");
	pT1_histo->GetXaxis()->SetLabelSize(0.04);
	pT1_histo->GetYaxis()->SetTitle("Number of events /2.8 GeV");
	pT1_histo->GetYaxis()->SetTitleOffset(1.5);
	pT1_histo->GetYaxis()->SetLabelSize(0.04);
	pT1_histo->SetMaximum(40);
	//mijenjanje boje histograma
	pT1_histo->SetLineColor(kGreen-2);
	pT2_histo->SetLineColor(kBlue-2);
	pT3_histo->SetLineColor(kRed-2);
	pT4_histo->SetLineColor(kYellow-2);
	pT1_histo->SetFillColor(kGreen-2);
	//legenda
	TLegend* pT_histo_leg;
	pT_histo_leg = new TLegend(0.9,0.7,0.5,0.9);
	pT_histo_leg->AddEntry(pT1_histo, "First decay lepton p_{T}", "l");
	pT_histo_leg->AddEntry(pT2_histo, "Secund decay lepton p_{T}", "l");
	pT_histo_leg->AddEntry(pT3_histo, "Third decay lepton p_{T}", "l");
	pT_histo_leg->AddEntry(pT4_histo, "Fourth decay lepton p_{T}", "l");
	pT_histo_leg->SetTextSize(0.04);
	pT_histo_leg->Draw();
	
	//crtanje na gornjoj desnoj strani platna
	c1->cd(2);
	Eta1_histo->Draw("HISTO");
	//crtanje histograma ostalih četica na istom platnu
	Eta2_histo->Draw("HISTO SAME");
	Eta3_histo->Draw("HISTO SAME");
	Eta4_histo->Draw("HISTO SAME");
	//Postavljanje x i y osi histograma
	Eta1_histo->GetXaxis()->SetTitle("Decay lepton Eta ");
	Eta1_histo->GetXaxis()->SetLabelSize(0.04);
	Eta1_histo->GetYaxis()->SetTitle("Number of events /0.1 ");
	Eta1_histo->GetYaxis()->SetLabelSize(0.04);
	Eta1_histo->SetMaximum(11);
	//mijenjanje boje histograma
	Eta1_histo->SetLineColor(kGreen-2);
	Eta1_histo->SetLineColor(kBlue-2);
	Eta2_histo->SetLineColor(kRed-2);
	Eta4_histo->SetLineColor(kYellow-2);
	Eta1_histo->SetFillColor(kGreen-2);
	//legenda
	TLegend* Eta_histo_leg;
	Eta_histo_leg = new TLegend(0.9,0.7,0.4,0.9);
	Eta_histo_leg->AddEntry(Eta1_histo, "First decay lepton pseudorapidity", "l");
	Eta_histo_leg->AddEntry(Eta2_histo, "Secund decay lepton pseudorapidity", "l");
	Eta_histo_leg->AddEntry(Eta3_histo, "Third decay lepton pseudorapidity", "l");
	Eta_histo_leg->AddEntry(Eta4_histo, "Fourth decay lepton pseudorapidity", "l");
	Eta_histo_leg->SetTextSize(0.04);
	Eta_histo_leg->Draw();
	
	//crtanje na donjoj lijevoj strani platna
	c1->cd(3);
	Phi1_histo->Draw("HISTO");
	//crtanje histograma ostalih četica na istom platnu
	Phi2_histo->Draw("HISTO SAME");
	Phi3_histo->Draw("HISTO SAME");
	Phi4_histo->Draw("HISTO SAME");
	//Postavljanje x i y osi histograma
	Phi1_histo->GetXaxis()->SetTitle("Decay lepton Phi [rad]");
	Phi1_histo->GetXaxis()->SetLabelSize(0.04);
	Phi1_histo->GetYaxis()->SetTitle("Number of events /0.1 rad");
	Phi1_histo->GetYaxis()->SetLabelSize(0.04);
	Phi1_histo->SetMaximum(6);
	//mijenjanje boje histograma
	Phi1_histo->SetLineColor(kGreen-2);
	Phi2_histo->SetLineColor(kBlue-2);
	Phi3_histo->SetLineColor(kRed-2);
	Phi4_histo->SetLineColor(kYellow-2);
	Phi1_histo->SetFillColor(kGreen-2);
	//legenda
	TLegend* Phi_histo_leg;
	Phi_histo_leg = new TLegend(0.9,0.7,0.4,0.9);
	Phi_histo_leg->AddEntry(Phi1_histo, "First decay lepton azim. angle", "l");
	Phi_histo_leg->AddEntry(Phi2_histo, "Secund decay lepton azim. angle", "l");
	Phi_histo_leg->AddEntry(Phi3_histo, "Third decay lepton azim. angle", "l");
	Phi_histo_leg->AddEntry(Phi4_histo, "Fourth decay lepton azim. angle", "l");
	Phi_histo_leg->SetTextSize(0.04);
	Phi_histo_leg->Draw();
	
	//crtanje na donjoj desnoj strani platna
	c1->cd(4);
	BDT1_histo->Draw("HISTO");
	//crtanje histograma ostalih četica na istom platnu
	BDT2_histo->Draw("HISTO SAME");
	BDT3_histo->Draw("HISTO SAME");
	BDT4_histo->Draw("HISTO SAME");
	//Postavljanje x i y osi histograma
	BDT1_histo->GetXaxis()->SetTitle("Decay lepton BDT");
	BDT1_histo->GetXaxis()->SetLabelSize(0.04);
	BDT1_histo->GetYaxis()->SetTitle("Number of events /0.33 ");
	BDT1_histo->GetYaxis()->SetTitleOffset(1.5);
	BDT1_histo->GetYaxis()->SetLabelSize(0.03);
	//mijenjanje boje histograma
	BDT1_histo->SetLineColor(kGreen-2);
	BDT2_histo->SetLineColor(kBlue-2);
	BDT3_histo->SetLineColor(kRed-2);
	BDT4_histo->SetLineColor(kYellow-2);
	BDT1_histo->SetFillColor(kGreen-2);
	//legenda
	TLegend* BDT_histo_leg;
	BDT_histo_leg = new TLegend(0.9,0.7,0.5,0.9);
	BDT_histo_leg->AddEntry(BDT1_histo, "First decay lepton BDT", "l");
	BDT_histo_leg->AddEntry(BDT2_histo, "Secund decay lepton BDT", "l");
	BDT_histo_leg->AddEntry(BDT3_histo, "Third decay lepton BDT", "l");
	BDT_histo_leg->AddEntry(BDT4_histo, "Fourth decay lepton BDT", "l");
	BDT_histo_leg->SetTextSize(0.04);
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
		Higgs_Histo->GetXaxis()->SetTitle("Higgs mass [GeV]");
		Higgs_Histo->GetXaxis()->SetLabelSize(0.04);
		Higgs_Histo->GetYaxis()->SetTitle("Events /2GeV");
		Higgs_Histo->GetYaxis()->SetTitleOffset(1.5);
		Higgs_Histo->GetYaxis()->SetLabelSize(0.04);
		Higgs_Histo->SetMaximum(100);
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


