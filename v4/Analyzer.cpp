#include<fstream>
#include<iostream>
#include<sstream>
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
            cout<<br_class<<"\t"<<ime_class<<"\t"<<px_class<<"\t"<<py_class<<"\t"<<pz_class<<"\t"<<E_class<<endl;          
        }
    }
}
