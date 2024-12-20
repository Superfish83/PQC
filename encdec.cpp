//
// encdec.cpp
// This file defines the ciphertext class, encryption and decryption functions
//

#pragma once
#include <stdlib.h>
#include "pkeScheme.h"

class CipherText {
public:
    Polynomial c0;
    Polynomial c1;

    // Encrypt the plaintext m
    CipherText(PRG prg, Polynomial* pk, Polynomial* m){
        Polynomial r;
        prg.sample_uniform_poly(&r, 2); // sample small random polynomial r

        // c0 = r*b + e0 + [q/2]m (mod P)
        prg.sample_DG_poly(&c0, SIGMA);
        c0 = (r * pk[1]) + c0;
        c0 = ((*m) * (P/2)) + c0;

        // c1 = r*a + e1 (mod Q)
        prg.sample_DG_poly(&c1, SIGMA);
        c1 = (r * pk[0]) + c1;
    }
};

// returns the encryption of a plaintext with encryption key pk
CipherText encrypt(PRG prg, Polynomial* pk, Polynomial* plain){
    return CipherText(prg, pk, plain);
}

// returns the decryption of a ciphertext with decryption key sk
Polynomial decrypt(CipherText cipher, Polynomial *sk){
    Polynomial plain;

    // \mu = c1 * s + c0
    plain = (cipher.c1 * (*sk)) - cipher.c0;
    // m = [(2/P)\mu]
    // round appropriately in mod 2 space
    int v;
    for(int i = 0; i < N; i++){
        v = plain.coef[i];
        if((P/4) <= v && v <= (3*P/4)) plain.coef[i] = 1;
        else plain.coef[i] = 0;
    }
    
    return plain;
}