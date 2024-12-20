//
// polynomial.cpp
// This file defines the class of polynomials,
// which are elements of the polynomial ring R = Z[X]/(X^N + 1) (mod P)
// R is the plaintext space of the implemented scheme.
//

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "pkeScheme.h"

// class of a cyclotomic polynomial,
// which is an element of R = Z[X]/(X^N + 1) (mod P) 
class Polynomial {
private:
public:
    // array that stores coefficients of the polynomial
    int coef[N];

    Polynomial(){
        for(int i = 0; i < N; i++){
            coef[i] = 0;
        }
    }

    Polynomial operator+(Polynomial &poly){
        Polynomial res;

        for(int i = 0; i < N; i++){
            res.coef[i] = ((coef[i] + poly.coef[i]) % P);
        }

        return res;
    }
    Polynomial operator-(Polynomial &poly){
        Polynomial res;

        for(int i = 0; i < N; i++){
            res.coef[i] = ((coef[i] + P - poly.coef[i]) % P);
        }

        return res;
    }
    Polynomial operator*(Polynomial &poly){
        Polynomial res;

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i + j >= N) res.coef[i+j-N] += (P - coef[i] * poly.coef[j]);
                else res.coef[i+j] += (coef[i] * poly.coef[j]);
            }
        }

        // confine in mod space
        for(int i = 0; i < N; i++){
            res.coef[i] = ((res.coef[i]) % P);
        }

        return res;
    }
    Polynomial operator*(int scalar){
        Polynomial res;

        for(int i = 0; i < N; i++){
            res.coef[i] = ((coef[i] * scalar) % P);
        }

        return res;
    }

    // copies and stores the coefficient from another polynomial
    void copyCoef(Polynomial *poly){
        for(int i = 0; i < N; i++){
            coef[i] = poly->coef[i];
        }
    }

    // prints the content of the polynomial
    void printPoly(bool verbose=false, bool newline=false){
        char buff[4096];
        char *p = buff;

        for(int i = N-1; i > 0; i--){
            if((coef[i] != 0) || verbose) {
                if(coef[i] == 1) p += sprintf(p, "x^%d%", i);
                else p += sprintf(p, "%dx^%d", coef[i], i);
                p += sprintf(p, "%c+ ", (newline ? '\n' : ' '));
            }
        }
        sprintf(p, "%d\n", coef[0]);

        printf("%s", buff);
    }

    // returns the L-inf norm of the polynomial ( ||P(x)|| )
    int norm_inf(){
        int norm = 0;
        for(int i = 0; i < N; i++){
            norm = (abs(coef[i]) > norm) ? abs(coef[i]) : norm;
        }
        return norm;
    }
};