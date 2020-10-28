//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 28 12:17:57 2020 by ROOT version 6.22/02
// from TTree Tree/Vjezbe 4
// found on file: Analysis.root
//////////////////////////////////////////////////////////

#ifndef Analyzer_h
#define Analyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#include <iostream>
using namespace std;
// Header file for the classes stored in the TTree if any.

class Analyzer 
{
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           br_class;
   string          *ime1_class;
   string          *ime2_class;
   Double_t        px1_class;
   Double_t        py1_class;
   Double_t        pz1_class;
   Double_t        pt1_class;
   Double_t        E1_class;
   Double_t        px2_class;
   Double_t        py2_class;
   Double_t        pz2_class;
   Double_t        pt2_class;
   Double_t        E2_class;

   // List of branches
   TBranch        *b_br_class;   //!
   TBranch        *b_ime1_class;   //!
   TBranch        *b_ime2_class;   //!
   TBranch        *b_px1_class;   //!
   TBranch        *b_py1_class;   //!
   TBranch        *b_pz1_class;   //!
   TBranch        *b_pt1_class;   //!
   TBranch        *b_E1_class;   //!
   TBranch        *b_px2_class;   //!
   TBranch        *b_py2_class;   //!
   TBranch        *b_pz2_class;   //!
   TBranch        *b_pt2_class;   //!
   TBranch        *b_E2_class;   //!
   
   //Varijable klase TH1F
   TH1F *Histo1;
   TH1F *Histo2;

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   //#dodana funkcija
   virtual void PlotHistogram();
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) 
   {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Analysis.root");
      if (!f || !f->IsOpen())
		{
         f = new TFile("Analysis.root");
      }
      f->GetObject("Tree",tree);

   }
   Init(tree);
}

Analyzer::~Analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) 
	   return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) 
	   return centry;
   if (fChain->GetTreeNumber() != fCurrent) 
   {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   ime1_class = 0;
   ime2_class = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("br_class", &br_class, &b_br_class);
   fChain->SetBranchAddress("ime1_class", &ime1_class, &b_ime1_class);
   fChain->SetBranchAddress("ime2_class", &ime2_class, &b_ime2_class);
   fChain->SetBranchAddress("px1_class", &px1_class, &b_px1_class);
   fChain->SetBranchAddress("py1_class", &py1_class, &b_py1_class);
   fChain->SetBranchAddress("pz1_class", &pz1_class, &b_pz1_class);
   fChain->SetBranchAddress("pt1_class", &pt1_class, &b_pt1_class);
   fChain->SetBranchAddress("E1_class", &E1_class, &b_E1_class);
   fChain->SetBranchAddress("px2_class", &px2_class, &b_px2_class);
   fChain->SetBranchAddress("py2_class", &py2_class, &b_py2_class);
   fChain->SetBranchAddress("pz2_class", &pz2_class, &b_pz2_class);
   fChain->SetBranchAddress("pt2_class", &pt2_class, &b_pt2_class);
   fChain->SetBranchAddress("E2_class", &E2_class, &b_E2_class);
   Notify();
}

Bool_t Analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analyzer_cxx
