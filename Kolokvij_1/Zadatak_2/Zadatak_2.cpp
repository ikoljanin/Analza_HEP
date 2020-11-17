#define Zadatak_2_cxx
#include "Zadatak_2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include<iostream>
#include <Riostream.h>
#include <TColor.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TH2F.h>

void Zadatak_2::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Zadatak_2.C
//      root> Zadatak_2 t
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
   }
}

void Zadatak_2::plot_histogram()
{
	//Histograv za A
	TH1F *ele_pt_histo;
	
	ele_pt_histo=new TH1F("ele_pt","Electron transversal momentum",30,0,150);//bin 5 GeV
	electron_2D_histo=new TH2F("PT vs SCAL","",30,0,150,80,-3,3);
	if (fChain == 0) 
	 {
		 return;
	 }
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	double scal;
	for (Long64_t jentry=0; jentry<100000;jentry++) 
   {
	  
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) 
		{
			break;
		}
		nb = fChain->GetEntry(jentry); 
		nbytes += nb;
		//PUNJENJE HISTOGRAMA ZA PT
		ele_pt_histo->Fill(ele_pt); 
		//2D HISTOGRAMA
		electron_2D_histo->Fill(ele_pt,scl_eta);
   }
	TCanvas *canvas_1 ;
	gStyle->SetOptStat(0);
	canvas_1= new TCanvas("c1","c1",1600,900);
	//podjela platna na pola
	canvas_1->Divide(2,1);
	//lijevi dio platna
	canvas_1->cd(1);
	gPad->SetLeftMargin(0.18);
	gPad->SetBottomMargin(0.20);
	ele_pt_histo->Draw("HISTO");
	ele_pt_histo->GetXaxis()->SetTitle("Electron p_{T} [GeV]");
	ele_pt_histo->GetXaxis()->SetLabelSize(0.04);
	ele_pt_histo->GetYaxis()->SetTitle("Number of events /5GeV");
	ele_pt_histo->GetYaxis()->SetLabelSize(0.04);
	//ele_pt_histo->SetTitle("Electron transversal momentum");
	ele_pt_histo->SetTitleFont(44);
	ele_pt_histo->SetLineColor(kRed);
	
	//desni dio
	canvas_1->cd(2);
	gPad->SetRightMargin(0.20);
	gPad->SetBottomMargin(0.20);
	electron_2D_histo->Draw("colz");
	electron_2D_histo->SetMinimum(-0.01);
	electron_2D_histo->SetStats(0);
	electron_2D_histo->SetTitle("Electron p_{T} - Electron eta");
	electron_2D_histo->SetTitleFont(44);
	electron_2D_histo->GetXaxis()->SetTitle("p_{T} [GeV]");
	electron_2D_histo->GetYaxis()->SetTitle("Eta [rad]");
	
	canvas_1->SaveAs("ElectronTraining.pdf");
}
