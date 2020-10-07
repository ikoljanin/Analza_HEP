#include"ElementaryParticle.h"

    ElementaryParticle::ElementaryParticle (double x, string y, bool z)
    {
        masa_class=x;
        ime_class=y;
        boson_class=z;
    }


    void ElementaryParticle::print()//poivanje funkcije za print
    {
         cout << "Masa cestice "<<ime_class<<" je = " << masa_class << " ova cestica je bozon = "<< boson_class<< endl;
        
    }

