//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec  2 12:06:42 2020 by ROOT version 6.22/02
// from TTree Tree/Lifetime decay data
// found on file: /home/public/data/Lifetime/Lifetime.root
//////////////////////////////////////////////////////////

#ifndef Lifetime_h
#define Lifetime_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <THStack.h>
#include <TGraph.h>
#include <TH2F.h>
#include <TF1.h>
#include <TStyle.h>
#include <TLatex.h>
#include <iostream>
using namespace std;

// Header file for the classes stored in the TTree if any.

class Lifetime {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         t;

   // List of branches
   TBranch        *b_t;   //!

   Lifetime(TTree *tree=0);
   virtual ~Lifetime();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void tau_bin();
   public :
	TH1F *t_histo;
	TF1 *t_fit, *t_fit_one,*lnL, *tau_fit;
	double suma_t=0.0,N;
	double sigma_1,sigma_2,sigma_3;
	double tau_min,tau_max;
	int bin_number;
};

#endif

#ifdef Lifetime_cxx
Lifetime::Lifetime(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/Lifetime/Lifetime.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/Lifetime/Lifetime.root");
      }
      f->GetObject("Tree",tree);

   }
   Init(tree);
}

Lifetime::~Lifetime()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Lifetime::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Lifetime::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Lifetime::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("t", &t, &b_t);
   Notify();
}

Bool_t Lifetime::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Lifetime::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Lifetime::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Lifetime_cxx
