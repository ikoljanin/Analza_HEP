#include "Analyzer.h"
using namespace std; 

//konstruktor klase
Analyzer::Analyzer ()
{
       
}

//funkcija za učitavanje i konvertiranje u root file
void Analyzer::read_function()
{
    // Varijable u koje se učitavaju podatci iz ulaznog dokumenta
    string ime_class;
    int br_class;
    double px_class,py_class,pz_class,E_class,pt_class;
    // File za isčitavanja
    ifstream MyReadFile("rezultati.txt");

    string line;
    //učitavanje .txt filea
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

//funkcija za konvertiranje u root file
void Analyzer::Convert_to_root()
{
	//file s ulaznim podatcima
	ifstream input_file("rezultati.txt");
	//konvertiranje filea s ulaznim podatcima u root file
	TFile *root_file = root_file = TFile::Open("rezultati.root","RECREATE");
	//pokazivač na objekt klase TTree (pokazivač na "stablo")
	TTree *tree = new TTree("T","Vjezbe 4");

   //kreiranje varijabli za brancheve (grane stabla)
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
	tree->Branch("px1_class",&px1_class,"px1_class/D");
	tree->Branch("py1_class",&py1_class,"py1_class/D");
	tree->Branch("pz1_class",&pz1_class,"pz1_class/D");
	tree->Branch("pt1_class",&pt1_class,"pt1_class/D");
	tree->Branch("E1_class" ,&E1_class, "E1_class/D");	
	tree->Branch("px2_class",&px2_class,"px2_class/D");
	tree->Branch("py2_class",&py2_class,"py2_class/D");
	tree->Branch("pz2_class",&pz2_class,"pz2_class/D");
	tree->Branch("pt2_class",&pt2_class,"pt2_class/D");
	tree->Branch("E2_class", &E2_class, "E2_class/D");
  
	string line;
	if(input_file.is_open())
    {
        while (getline(input_file,line))
        {
            stringstream linestream(line);
            //učitavanje varijabli "jedna po jedna"
            linestream>>br_class>>ime1_class>>px1_class>>py1_class>>pz1_class>>pt1_class>>E1_class>>ime2_class>>px2_class>>py2_class>>pz2_class>>pt2_class>>E2_class;
			tree->Fill();
			//cout<<br_class<<endl;
			//cout<<br_class<<"\t"<<ime_class<<"\t"<<px_class<<"\t"<<py_class<<"\t"<<pz_class<<"\t"<<E_class<<endl;          
        }
    }
	tree->Print();
	tree->Write();

	//input_file.close;
	delete root_file;
}
