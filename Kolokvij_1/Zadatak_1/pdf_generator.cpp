#include <iostream>
#include"PDFGenerator.h"
using namespace std;

int main() 
{
	srand(time(NULL));    
	PDFGenerator *A;
	A=new PDFGenerator();
	char filename[] = "rezultati.txt";
	remove(filename); 
	A->GenerateQuadraticPDF();
    return 0;
}
