//
// psg.cpp
// This file defines the pseudorandom generator class,
// and sampling functions from distributions
//

#pragma once
#include <random>
#include <chrono>
#include "polynomial.cpp"

using namespace std;

// Pseudorandom generator class
class PRG {
private:
    bool initialized = false;
    mt19937 gen;
public:
    // initialize the PRG (seed the number generator)
    void init(){
        // set the seed of PRG with current system time in nanoseconds
        const auto now = chrono::high_resolution_clock::now();
        const long ns = chrono::duration_cast<chrono::nanoseconds>(
            now.time_since_epoch()).count();
        mt19937 _gen(ns);
        gen = _gen;

        initialized = true;
    }

    // Samples a polynomial from uniform distribution
    void sample_uniform_poly(Polynomial *poly, int mod=P){
        if(!initialized) return;

        uniform_int_distribution<int> dis(0,mod-1);

        for(int i = 0; i < N; i++){
            poly->coef[i] = dis(gen);
        }
    }

    // Samples a polynomial from Discrete Gaussian distribution with std=sigma
    void sample_DG_poly(Polynomial *poly, double sigma){
        if(!initialized) return;

        normal_distribution<double> dis(0.0, sigma);

        for(int i = 0; i < N; i++){
            int v = round(dis(gen));
            // confine the coefficient in the modular space
            poly->coef[i] = (v>=0) ? v : (v+P);
        }
    }
};