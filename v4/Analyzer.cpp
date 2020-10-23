#include<fstream>
#include<iostream>
#include<sstream>
#include"TROOT.h"
#include"TChain.h"
#include"TFile.h"
#include"TApplication.h"
#include"Analyzer.h"

using namespace std;

 //konstruktor klase
 Analyzer::Analyzer ()
    {
       
    }

//funkcija za učitavanje 
void Analyzer::read_function()
{
    // Varijable u koje se učitavaju podatci iz ulaznog dokumenta
    string ime_class;
    int br_class;
    double px_class,py_class,pz_class,E_class;

    // Read from the text file
    ifstream MyReadFile("rezultati.txt");
    
    string line;
    
     if(MyReadFile.is_open())
    {
        while (getline(MyReadFile,line))
        {
            stringstream linestream(line);
            //učitavanje varijabli "jedna po jedna"
            linestream>>br_class>>ime_class>>px_class>>py_class>>pz_class>>E_class;
            //cout<<br_class<<"\t"<<ime_class<<"\t"<<px_class<<"\t"<<py_class<<"\t"<<pz_class<<"\t"<<E_class<<endl;          
        }
    }
}

//funkcija za konvertiranje u root file
void Analyzer::Convert_to_root()
{
	//definiranje brancheva
   Int_t           br_class;
   Char_t          ime1_class;
   Char_t          ime2_class;
   Double_t        px1_class;
   Double_t        py1_class;
   Double_t        pz1_class;
   Double_t        px2_class;
   Double_t        py2_class;
   Double_t        pz2_class;
   Double_t        E1_class;
   Double_t        E2_class;
   

   Tstring MyReadFile = "rezultati.root";

   TFile *hfile = hfile = TFile::Open(MyReadFile,"RECREATE");//otvaranje root filea

	//kreiranje i imenovanje "stabla" kao pokazivača na objekt klase TTree
   TTree *tree = new TTree("T","Vjezba 4");
   //dodavanje "brancheva" stablu
   tree->Branch("br_class",&br_class,"br_class/I");
   tree->Branch("ime1_class",&ime1_class,"Flag/C");
   tree->Branch("ime2_class",&ime2_class,"ime2_class/C");
   tree->Branch("px1_class",&px1_class,"px1_class/LF");
   tree->Branch("py1_class",&py1_class,"py1_class/LF");
   tree->Branch("pz1_class",&pz1_class,"pz1_class/LF");
   tree->Branch("px2_class",&px2_class,"px1_class/LF");
   tree->Branch("py2_class",&py2_class,"py2_cLass/LF");
   tree->Branch("pz2_class",&pz2_class,"pz2_class/LF");
    
	//ifstream MyReadFile("rezultati.txt");
	string line;
    
    if(MyReadFile.is_open())
    {
        while (getline(MyReadFile,line))
        {
            stringstream linestream(line);
            //učitavanje varijabli "jedna po jedna"
            linestream>>br_class>>ime1_class>>px1_class>>py1_class>>pz1_class>>E1_class>>ime2_class>>px2_class>>py2_class>>pz2_class>>E2_class;
            tree->Fill();     
        }
    }
			 
   tree->Print();
   tree->Write();

   fclose(hfile);
   delete hfile;
}
