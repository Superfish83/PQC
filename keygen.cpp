//
// keygen.cpp
// This file defines the Encryption Key class, with random key sampling functions.
//

#pragma once
#include <stdlib.h>
#include "pkeScheme.h"

class EncKey {
public:
    Polynomial sk;
    Polynomial pk[2];

    // samples secret key and public key.
    // sk = s <- \Chi = {0,1}^N
    // pk = (b, a) = (as+e (mod P), a)
    EncKey(PRG prg){
        prg.sample_uniform_poly(&sk, 2); // sample sk uniformly from \Chi
        prg.sample_uniform_poly(&pk[0]); // sample a = pk[1] uniformly from (Z_P)^N
        prg.sample_DG_poly(&pk[1]); // sample e <- DG
        pk[1] = (pk[0] * sk) + pk[1]; 
    }
};

EncKey KeyGen(PRG prg){
    return EncKey(prg);
}