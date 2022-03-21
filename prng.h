#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define a 1664525UL
#define c 1013904223UL
#define m INT_MAX

unsigned int seed = 0;

void changeSeed(unsigned int newSeed) {
    seed = newSeed;
}

unsigned int nextRand() {
    unsigned long s = ((a * (unsigned long) seed + c)) % m;
    seed = (unsigned int) s;
    return seed;
}

unsigned int nextRandLim(int min, int max) {
    return nextRand() % (max - min + 1) + min;
}

double nextDouble() {
    return ((double) nextRand()) / m;
}

bool nextBool() {
    return nextDouble() < 0.5;
}

unsigned char nextChar() {
    return nextRand() % UCHAR_MAX;
}