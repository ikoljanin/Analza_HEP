// dva studenta; primjer konstruktora i funkcije s pokazivačima

#include <iostream>
using namespace std;

class Student
{

   public:
    //varijable za svakog studenta (svojstva)
    double ocjena;
    double visina;
    string ime;

    // konstruktor ("alat" za inicijalizaciju objekata klase)
    Student(double o, double v, string i) 
    {
        ocjena = o;
        visina = v;
        ime = i;
    }
    
};
// funkcija s pokazivačima objektima klase kao ulaznim parametrima
void studenti(Student *s1, Student *s2) 
    {

        // prosječna ocjena 
        double average = (s1->ocjena + s2->ocjena) / 2;
        cout << "Prosjecna ocjena dvaju studenata je = " << average << endl;
        cout <<s1->ime<<" je visok "<<s1->visina<<", a položio je s ocjenom "<<s1->ocjena<<" dok je "<<s2->ime<<" visok "<<s2->visina<<" te je stekao ocjenu "<<s2->ocjena<<endl;
    } 


int main() 
{
    //Student student1(5.0,180.0,"Marko"), student2(4.0,170,"Ivan");
    //pokazivači na objekte klase
    Student *student1;
    Student *student2;

    //inicijalizacija objekata preko konstruktora klase    
    student1 = new Student(5.0,180.0,"Marko");
    student2 = new Student(4.0,170,"Ivan");

    //funkciji se šalju pokazivači na objekte klase
    studenti(student1, student2);
    //alternativa je studenti (*student1,*student2), ali onda funkcija void studenti (Student s1, Student s2).....s1.ocjena.....s2.ocjena

    return 0;
}
