#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "pkeScheme.h"

using namespace std;

int main(){
    printf("Hello cpp!\n");

    PRG prg;
    prg.init();
    
    Polynomial m;
    m.coef[0] = 1;
    m.coef[3] = 1;
    m.coef[100] = 1;
    EncKey key(prg);

    printf("Secret key:\n");
    key.sk.printPoly();

    printf("\n\nplaintext:\n");
    m.printPoly();

    CipherText c = encrypt(prg, key.pk, &m);
    printf("\n\nc0 of ciphertext:\n");
    c.c0.printPoly();

    Polynomial dec = decrypt(c, &key.sk);
    printf("\n\ndecrypted ciphertext:\n");
    dec.printPoly();

    return 0;
}