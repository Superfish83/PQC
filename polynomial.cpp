#define N 16
#define P 3329

#pragma once
#include <stdio.h>
#include <stdlib.h>

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
    Polynomial operator*(Polynomial &poly){
        Polynomial res;

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i + j >= N) res.coef[i+j-N] -= (coef[i] * poly.coef[j]);
                else res.coef[i+j] += (coef[i] * poly.coef[j]);
            }
        }

        // confine in mod space
        for(int i = 0; i < N; i++){
            while(res.coef[i] < 0) res.coef[i] += N*P;
            res.coef[i] = ((res.coef[i]) % P);
        }

        return res;
    }

    void printPoly(bool verbose=false){
        char buff[4096];
        char *p = buff;

        for(int i = N-1; i > 0; i--){
            if((coef[i] != 0) || verbose) p += sprintf(p, "%dx^%d + ", coef[i], i);
        }
        sprintf(p, "%d\n", coef[0]);

        printf("%s", buff);
    }
};