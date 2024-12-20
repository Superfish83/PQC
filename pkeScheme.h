//
// This header file includes all classes and functions needed for
// the implementation of the BFV public key encryption scheme.
//

#ifndef N

#define N 256
#define P 3329 // Polynomial modulus (both plaintext and ciphertext)
#define SIGMA 1.414

using namespace std;

#include "polynomial.cpp"
#include "prg.cpp"
#include "keygen.cpp"
#include "encdec.cpp"

#endif