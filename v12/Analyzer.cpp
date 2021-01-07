#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

//pozadinski događaji
void Analyzer::Loop_b()
{
	Init(b_tree);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   cout<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) 
			break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	  Back_histo->Fill(ele_pt);
   }
   
}

//signalni događaji
void Analyzer::Loop_signal()
{
	Init(signal_tree);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   cout<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) 
			break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	  Signal_histo->Fill(ele_pt);
   }
   
}

void Analyzer::Plot_histogram()
{
	TCanvas *canvas;
	canvas= new TCanvas("","",1600,900);
	canvas->Divide(1,2);
	canvas->cd(1);
	Signal_histo->Draw();
	Back_histo->Draw("SAME");
	//canvas->cd(2);
	//OSTALIH 7 VARIJABLI
	canvas->SaveAs("test.pdf");
	
}

void Analyzer::TMVATraining()
{
	TTree *tree=new TTree();
	if (tree == 0) 
	{
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TMVA.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("TMVA.root");
      }
      f->GetObject("background",b_tree);
	  f->GetObject("signal",signal_tree);
   }
	
   TMVA::Tools::Instance();
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
	//odabir varijabli
   dataloader->AddVariable( "ele_pt", 'F' );
   dataloader->AddVariable( "scl_eta", 'F' );
   dataloader->AddVariable( "ele_hadronicOverEm", 'F' );
   dataloader->AddVariable( "ele_gsfchi2", 'F' );
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;
   dataloader->AddSignalTree    ( signal_tree,     signalWeight );
   dataloader->AddBackgroundTree( b_tree, backgroundWeight );
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";
   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );
   // Cut optimisation
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators
   factory->TrainAllMethods();

   factory->TestAllMethods();

   factory->EvaluateAllMethods();

   outputFile->Close();
   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;
   delete factory;
   delete dataloader;
}


