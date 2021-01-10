#define Analyzer_cxx
#define TMVATraining_cxx
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
   //cout<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) 
			break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	  
	  Back_histo[0]->Fill(scl_eta);
	  Back_histo[1]->Fill(ele_hadronicOverEm);
	  Back_histo[2]->Fill(ele_gsfchi2);
	  Back_histo[3]->Fill(ele_fbrem);
	  Back_histo[4]->Fill(ele_ep);
	  Back_histo[5]->Fill(ele_eelepout);
	  Back_histo[6]->Fill(ele_pfChargedHadIso);
	  Back_histo[7]->Fill(ele_pt);
   }
   
}

//signalni događaji
void Analyzer::Loop_signal()
{
	Init(signal_tree);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   //cout<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) 
			break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	  
	  Signal_histo[0]->Fill(scl_eta);
	  Signal_histo[1]->Fill(ele_hadronicOverEm);
	  Signal_histo[2]->Fill(ele_gsfchi2);
	  Signal_histo[3]->Fill(ele_fbrem);
	  Signal_histo[4]->Fill(ele_ep);
	  Signal_histo[5]->Fill(ele_eelepout);
	  Signal_histo[6]->Fill(ele_pfChargedHadIso);
	  Signal_histo[7]->Fill(ele_pt);
   }
   
}

void Analyzer::Plot_histogram()
{
	int i;
	double max_b,max_s;
	TCanvas *canvas;
	canvas= new TCanvas("","",1600,900);
	canvas->Divide(4,2);
	gStyle->SetOptStat(0000);
	
	//#1
	canvas->cd(1);
	i=0;
	gPad->SetLeftMargin(0.2);
	gPad->SetBottomMargin(0.2);
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	Back_histo[i]->SetLineColor(kRed);
	Signal_histo[i]->GetXaxis()->SetTitle("scl_eta");
    Signal_histo[i]->GetYaxis()->SetTitle("Events");
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	//određivanje maksimuma y osi
	max_b=Back_histo[i]->GetMaximum();
	max_s=Signal_histo[i]->GetMaximum();
	if(max_b<max_s)
	{
		Signal_histo[i]->SetMaximum(max_s+0.1*max_s);//0.1*max_S čisto da ostane malo mista iznad histograma
	}
	else if(max_b>max_s)
	{
		Signal_histo[i]->SetMaximum(max_b+0.1*max_b);
	}
	legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->AddEntry(Signal_histo[i], "Signal");
	legend->AddEntry(Back_histo[i], "Background");
	legend->SetTextSize(0.03);
	legend->Draw();

	//#2
	canvas->cd(2);
	i=1;
	gPad->SetLeftMargin(0.2);
	gPad->SetBottomMargin(0.2);
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	Back_histo[i]->SetLineColor(kRed);
	Signal_histo[i]->GetXaxis()->SetTitle("ele_hadronicOverEm");
    Signal_histo[i]->GetYaxis()->SetTitle("Events");
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	//određivanje maksimuma y osi
	max_b=Back_histo[i]->GetMaximum();
	max_s=Signal_histo[i]->GetMaximum();
	if(max_b<max_s)
	{
		Signal_histo[i]->SetMaximum(max_s+0.1*max_s);//0.1*max_S čisto da ostane malo mista iznad histograma
	}
	else if(max_b>max_s)
	{
		Signal_histo[i]->SetMaximum(max_b+0.1*max_b);
	}
	legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->AddEntry(Signal_histo[i], "Signal");
	legend->AddEntry(Back_histo[i], "Background");
	legend->SetTextSize(0.03);
	legend->Draw();
	
	//#3
	canvas->cd(3);
	i=2;
	gPad->SetLeftMargin(0.2);
	gPad->SetBottomMargin(0.2);
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	Back_histo[i]->SetLineColor(kRed);
	Signal_histo[i]->GetXaxis()->SetTitle("ele_gsfchi2");
    Signal_histo[i]->GetYaxis()->SetTitle("Events");
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	//određivanje maksimuma y osi
	max_b=Back_histo[i]->GetMaximum();
	max_s=Signal_histo[i]->GetMaximum();
	if(max_b<max_s)
	{
		Signal_histo[i]->SetMaximum(max_s+0.1*max_s);//0.1*max_S čisto da ostane malo mista iznad histograma
	}
	else if(max_b>max_s)
	{
		Signal_histo[i]->SetMaximum(max_b+0.1*max_b);
	}
	legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->AddEntry(Signal_histo[i], "Signal");
	legend->AddEntry(Back_histo[i], "Background");
	legend->SetTextSize(0.03);
	legend->Draw();
	
	//#4
	canvas->cd(4);
	i=3;
	gPad->SetLeftMargin(0.2);
	gPad->SetBottomMargin(0.2);
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	Back_histo[i]->SetLineColor(kRed);
	Signal_histo[i]->GetXaxis()->SetTitle("ele_fbrem");
    Signal_histo[i]->GetYaxis()->SetTitle("Events");
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	//određivanje maksimuma y osi
	max_b=Back_histo[i]->GetMaximum();
	max_s=Signal_histo[i]->GetMaximum();
	if(max_b<max_s)
	{
		Signal_histo[i]->SetMaximum(max_s+0.1*max_s);//0.1*max_S čisto da ostane malo mista iznad histograma
	}
	else if(max_b>max_s)
	{
		Signal_histo[i]->SetMaximum(max_b+0.1*max_b);
	}
	legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->AddEntry(Signal_histo[i], "Signal");
	legend->AddEntry(Back_histo[i], "Background");
	legend->SetTextSize(0.03);
	legend->Draw();
	
	//#5
	canvas->cd(5);
	i=4;
	gPad->SetLeftMargin(0.2);
	gPad->SetBottomMargin(0.2);
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	Back_histo[i]->SetLineColor(kRed);
	Signal_histo[i]->GetXaxis()->SetTitle("ele_ep");
    Signal_histo[i]->GetYaxis()->SetTitle("Events");
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	//određivanje maksimuma y osi
	max_b=Back_histo[i]->GetMaximum();
	max_s=Signal_histo[i]->GetMaximum();
	if(max_b<max_s)
	{
		Signal_histo[i]->SetMaximum(max_s+0.1*max_s);//0.1*max_S čisto da ostane malo mista iznad histograma
	}
	else if(max_b>max_s)
	{
		Signal_histo[i]->SetMaximum(max_b+0.1*max_b);
	}
	legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->AddEntry(Signal_histo[i], "Signal");
	legend->AddEntry(Back_histo[i], "Background");
	legend->SetTextSize(0.03);
	legend->Draw();
	
	//#6
	canvas->cd(6);
	i=5;
	gPad->SetLeftMargin(0.2);
	gPad->SetBottomMargin(0.2);
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	Back_histo[i]->SetLineColor(kRed);
	Signal_histo[i]->GetXaxis()->SetTitle("ele_eelepout");
    Signal_histo[i]->GetYaxis()->SetTitle("Events");
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	//određivanje maksimuma y osi
	max_b=Back_histo[i]->GetMaximum();
	max_s=Signal_histo[i]->GetMaximum();
	if(max_b<max_s)
	{
		Signal_histo[i]->SetMaximum(max_s+0.1*max_s);//0.1*max_S čisto da ostane malo mista iznad histograma
	}
	else if(max_b>max_s)
	{
		Signal_histo[i]->SetMaximum(max_b+0.1*max_b);
	}
	legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->AddEntry(Signal_histo[i], "Signal");
	legend->AddEntry(Back_histo[i], "Background");
	legend->SetTextSize(0.03);
	legend->Draw();
	
	//#7
	canvas->cd(7);
	i=6;
	gPad->SetLeftMargin(0.2);
	gPad->SetBottomMargin(0.2);
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	Back_histo[i]->SetLineColor(kRed);
	Signal_histo[i]->GetXaxis()->SetTitle("ele_pfChargedHadIso");
    Signal_histo[i]->GetYaxis()->SetTitle("Events");
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	//određivanje maksimuma y osi
	max_b=Back_histo[i]->GetMaximum();
	max_s=Signal_histo[i]->GetMaximum();
	if(max_b<max_s)
	{
		Signal_histo[i]->SetMaximum(max_s+0.1*max_s);//0.1*max_S čisto da ostane malo mista iznad histograma
	}
	else if(max_b>max_s)
	{
		Signal_histo[i]->SetMaximum(max_b+0.1*max_b);
	}
	legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->AddEntry(Signal_histo[i], "Signal");
	legend->AddEntry(Back_histo[i], "Background");
	legend->SetTextSize(0.03);
	legend->Draw();
	
	//#8
	canvas->cd(8);
	i=7;
	gPad->SetLeftMargin(0.2);
	gPad->SetBottomMargin(0.2);
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	Back_histo[i]->SetLineColor(kRed);
	Signal_histo[i]->GetXaxis()->SetTitle("ele_pt");
    Signal_histo[i]->GetYaxis()->SetTitle("Events");
	Signal_histo[i]->Draw();
	Back_histo[i]->Draw("SAME");
	//određivanje maksimuma y osi
	max_b=Back_histo[i]->GetMaximum();
	max_s=Signal_histo[i]->GetMaximum();
	if(max_b<max_s)
	{
		Signal_histo[i]->SetMaximum(max_s+0.1*max_s);//0.1*max_S čisto da ostane malo mista iznad histograma
	}
	else if(max_b>max_s)
	{
		Signal_histo[i]->SetMaximum(max_b+0.1*max_b);
	}
	legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->AddEntry(Signal_histo[i], "Signal");
	legend->AddEntry(Back_histo[i], "Background");
	legend->SetTextSize(0.03);
	legend->Draw();
		
	//spremanje platna
	canvas->SaveAs("Electron_8.pdf");
	
}

void Analyzer::TMVATraining(TString myMethodList )
{
	
   TMVA::Tools::Instance();
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
	//odabir varijabli
   dataloader->AddVariable( "ele_ep", 'F' );
   dataloader->AddVariable( "ele_pfChargedHadIso", 'F' );
   dataloader->AddVariable( "ele_fbrem", 'F' );
   dataloader->AddVariable( "ele_pt", 'F' );
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;
   dataloader->AddSignalTree    ( signal_tree,     signalWeight );
   dataloader->AddBackgroundTree( b_tree, backgroundWeight );
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";
   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );
   // Cut optimisation
	if (myMethodList=="MLP")
    factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N:TestRate=0.5:!UseRegulator" );

	if (myMethodList=="BDTG") // Gradient Boost
    factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=1:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );
	if (myMethodList=="BDT")  // Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
  
   factory->TrainAllMethods();

   factory->TestAllMethods();

   factory->EvaluateAllMethods();

   outputFile->Close();
   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;
   
   delete factory;
   delete dataloader;
   
   
}

void Analyzer :: plot(TString myMethodList)
{
	TCanvas *canvas;
	TCanvas *canvas1;
	canvas= new TCanvas("","",1600,900);
	canvas1= new TCanvas("","",1600,900);
	canvas->Divide(2,1);
	TFile *f = new TFile("TMVA.root"); 
	if(myMethodList=="BDTG")
	{
		TGraph* signal = (TGraph*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_S");
		TGraph* bkg = (TGraph*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_B");
		TH1F* sig_bkg_eff = (TH1F*)f->Get("dataset/Method_BDT/BDTG/MVA_BDTG_effBvsS");
		signal->SetTitle("Signal");
		bkg->SetTitle("Background");
		sig_bkg_eff->SetTitle("SIGvsBKG");
		cout<<"Udio propustenog backgrounda za 90% signala:"<<sig_bkg_eff->Interpolate(0.9)<<endl;
		canvas->cd(1);
		signal->Draw();
		canvas->cd(2);
		bkg->Draw();
		canvas->SaveAs("BDTG_result.pdf");
		canvas1->cd();
		sig_bkg_eff->Draw();
	}
	if(myMethodList=="BDT")
	{
		TGraph* signal = (TGraph*)f->Get("dataset/Method_BDT/BDT/MVA_BDT_S");
		TGraph* bkg = (TGraph*)f->Get("dataset/Method_BDT/BDT/MVA_BDT_B");
		TH1F* sig_bkg_eff = (TH1F*)f->Get("dataset/Method_BDT/BDT/MVA_BDT_effBvsS");
		signal->SetTitle("Signal");
		bkg->SetTitle("Background");
		sig_bkg_eff->SetTitle("SIGvsBKG");
		cout<<"Udio propustenog backgrounda za 90% signala:"<<sig_bkg_eff->Interpolate(0.9)<<endl;
		canvas->cd(1);
		signal->Draw();
		canvas->cd(2);
		bkg->Draw();
		canvas->SaveAs("BDT_result.pdf");
		canvas1->cd();
		sig_bkg_eff->Draw();
	}
	if(myMethodList=="MLP")
	{
		TGraph* signal = (TGraph*)f->Get("dataset/Method_MLP/MLP/MVA_MLP_S");
		TGraph* bkg = (TGraph*)f->Get("dataset/Method_MLP/MLP/MVA_MLP_B");
		TH1F* sig_bkg_eff = (TH1F*)f->Get("dataset/Method_MLP/MLP/MVA_MLP_effBvsS");
		signal->SetTitle("Signal");
		bkg->SetTitle("Background");
		sig_bkg_eff->SetTitle("SIGvsBKG");
		cout<<"Udio propustenog backgrounda za 90% signala:"<<sig_bkg_eff->Interpolate(0.9)<<endl;
		canvas->cd(1);
		signal->Draw();
		canvas->cd(2);
		bkg->Draw();
		canvas->SaveAs("MLP_result.pdf");
		canvas1->cd();
		sig_bkg_eff->Draw();
	}	
	canvas1->SaveAs("SIG_vs_BKG.pdf");
	 
}

 
