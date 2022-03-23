#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>

/*
#define a 1664525UL
#define c 1013904223UL
#define m INT_MAX
*/

unsigned long long seed = 27;

void changeSeed(unsigned int newSeed) {
    seed = newSeed;
}

unsigned long long nextRand() {
    __uint128_t mod = (18446744073709551615ULL);

    __uint128_t g1 = pow(3, 7);
    __uint128_t g2 = 1;
    __uint128_t g3 = 1;

    for (int i = 0; i < 5; i++) {
        g2 = (g2 * (seed % mod)) % mod;
    }

    for (int i = 0; i < 3; i++) {
        g3 = (g3 * (seed % mod)) % mod;
    }

    __uint128_t gx = (g1 * ((g2 + g3 + 1) % mod)) % mod;
    seed = gx;

    return gx;
}

unsigned int nextRandLim(int min, int max) {
    return nextRand() % (max - min + 1) + min;
}

double nextDouble() {
    return ((double) nextRand()) / (pow(2, 64) - 1);
}

bool nextBool() {
    return nextDouble() < 0.5;
}

unsigned char nextChar() {
    return nextRand() % UCHAR_MAX;
}