#include <iostream>
#include <math.h>

double mycube (double a)
{
    double b;
    b=a*a*a;
    return b;
}

int main() 
{
    double a,b;
    std::cout<<"Unesi ralan broj \n";
    std::cin>>a;
    b=mycube(a);
    std ::cout<< b;
    std::cout << "\n" ;
    return 0;
}
