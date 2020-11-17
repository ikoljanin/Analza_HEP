#include"PDFGenerator.h"

	//pozivanje konstruktora klase :: određuje kojoj klasi konstruktor pripada
    PDFGenerator::PDFGenerator () 
    {
        cout<<"Objekt je kreiran"<<endl;
    }

    void PDFGenerator::GenerateQuadraticPDF()//poivanje funkcije za print
    {
		//generiranje random brojevaa između -1 i 1 ...(rand()%1000)/1000; generira brojeve od 0 do 1
		for(int i=1;i<=10000;i++)
		{
			random_x=-1.+(1.-(-1.))*(rand()%1000)/1000;
			random_y=-1.+(1.-(-1.))*(rand()%1000)/1000;
			//cout<<random_x<<" "<<random_y<<endl;
			f_x=-(3/4)*random_x*random_x+3/4;
			//ako je par prihvaćen kreira s ehistogram
			if(random_y<=f_x)
			{
				ofstream file;
				file.open ("rezultati.txt",ios_base::app); 
				file <<random_x<<"\t"<<random_y<<endl;
				file.close(); 
			}
		}	

    }

