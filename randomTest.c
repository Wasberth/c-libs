#include <stdio.h>

#include "prng.h"

int main() {
    for (int i = 0; i < 50; i++) {
        printf("%llu\n", nextRand());
    }
}