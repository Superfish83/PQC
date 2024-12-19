#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "BFVscheme.h"

using namespace std;

int main(){
    printf("Hello cpp!\n");

    PRG prg;
    prg.init();

    Polynomial poly1;
    Polynomial poly2;
    poly1.coef[0] = 1;
    poly1.coef[1] = 1;
    poly1.coef[2] = 1;
    poly2.coef[1] = 1;
    poly2.coef[3] = 1;
    prg.sample_DG_poly(&poly1, 5.0);
    //prg.sample_uniform_poly(&poly1);
    printf("P1(x)\n");
    poly1.printPoly();
    printf("P2(x)\n");
    poly2.printPoly();
    Polynomial poly3 = poly1 * poly2;
    printf("P3(x)=P1(x)*P2(X)\n");
    poly3.printPoly();
    Polynomial poly4 = poly1 + poly2;
    printf("P4(x)=P1(x)+P2(X)\n");
    poly4.printPoly();

    return 0;
}