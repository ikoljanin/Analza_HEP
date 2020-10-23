#include <iostream>
#include <string>
#include<fstream>
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TApplication.h"
#include "Analyzer.h"
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
    double px_class,py_class,pz_class,E_class,pt_class;

    // File za isčitavanja
    ifstream MyReadFile("rezultati.txt");
	
    string line;
    
    if(MyReadFile.is_open())
    {
        while (getline(MyReadFile,line))
        {
            stringstream linestream(line);
            //učitavanje varijabli "jedna po jedna"
            linestream>>br_class>>ime_class>>px_class>>py_class>>pz_class>>pt_class>>E_class;
			//cout<<br_class<<"\t"<<ime_class<<"\t"<<px_class<<"\t"<<py_class<<"\t"<<pz_class<<"\t"<<E_class<<endl;          
        }
    }
}

/*//funkcija za konvertiranje u root file (bez kreiranja stabla)
void Analyzer::Convert_to_root()
{
	string ime_class;
    int br_class;
    double px_class,py_class,pz_class,E_class,pt_class;
	
	ifstream MyReadFile("rezultati.txt");
	ofstream root_file;
    root_file.open ("rezultati.root",ios_base::app);
	string line;

	if(MyReadFile.is_open())
    {
        while (getline(MyReadFile,line))
        {
            stringstream linestream(line);
            //učitavanje varijabli "jedna po jedna"
            linestream>>br_class>>ime_class>>px_class>>py_class>>pz_class>>pt_class>>E_class;
			root_file<<br_class<<"\t"<<ime_class<<"\t"<<px_class<<"\t"<<py_class<<"\t"<<pz_class<<"\t"<<E_class<<endl;      
        }
    }
	MyReadFile.close();
	root_file.close();
}

//funkcija za konvertiranje u root file
void Analyzer::Convert_to_root()
{
	TFILE *fp = fopen("rezultati.txt","r");
	TFile *hfile = hfile = TFile::Open("rezultati.root","RECREATE");

   //kreiranje varijabli za brancheve
	Int_t           br_class;
	
	Char_t          ime1_class;
	Double_t        px1_class;
	Double_t        py1_class;
	Double_t        pz1_class;
	Double_t		pt1_class;
	Double_t        E1_class;
	
	Char_t          ime2_class;
	Double_t        px2_class;
	Double_t        py2_class;
	Double_t        pz2_class;
	Double_t		pt2_class;
	Double_t        E2_class;

	//dodavanje "brancheva" stablu
	tree->Branch("br_class",&br_class,"br_class/I");
	tree->Branch("ime1_class",&ime1_class,"Flag/C");
	tree->Branch("ime2_class",&ime2_class,"ime2_class/C");
	tree->Branch("px1_class",&px1_class,"px1_class/LF");
	tree->Branch("py1_class",&py1_class,"py1_class/LF");
	tree->Branch("pz1_class",&pz1_class,"pz1_class/LF");
	tree->Branch("pt1_class",&pt1_class,"pt1_class/LF");
	tree->Branch("E1_class" ,&E1_class, "E1_class/LF");	
	tree->Branch("px2_class",&px2_class,"px2_class/LF");
	tree->Branch("py2_class",&py2_class,"py2_cLass/LF");
	tree->Branch("pz2_class",&pz2_class,"pz2_class/LF");
	tree->Branch("pt2_class",&pt2_class,"pt2_class/LF");
	Tree->Branch("E2_class", &E2_class, "E2_class/LF");
  
	char line[80];
	while (fgets(line,80,fp)) 
	{
      sscanf(&line[0],"%d %c %c %lf %lf %lf %lf  %lf %lf %lf %lf %lf %lf",
      &br_class,&ime1_class,&ime2_class,&px1_class,&py1_class,&pz1_class,&px2_class,&py2_cLass,&pz2_class,&pt1_class,&pt2_class,&E1_class,&E2_class);
      tree->Fill();
	}
	tree->Print();
	tree->Write();

	fclose(fp);
	delete hfile;

}*/