//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#include "utils.h"

void doubleArraySize(size_t n, unsigned *&arr) {
    auto *out = new unsigned[n * 2];
    for (size_t i = 0; i < n; ++i) {
        out[i] = arr[i];
    }
    delete arr;
    arr = out;
}

unsigned *copyDoubleArraySize(size_t n, unsigned int *arr) {
    auto *out = new unsigned[n * 2];
    for (size_t i = 0; i < n; ++i) {
        out[i] = arr[i];
    }
    return out;
}

size_t eraseEndingZeroes(size_t n, unsigned* arr) {
    size_t nonTailLength = n;
    while (nonTailLength != 0 && arr[nonTailLength - 1] == 0) --nonTailLength;
    auto *out = new unsigned[nonTailLength];
    copy(arr, 0, out, nonTailLength);
    return nonTailLength;
}

void copy(const unsigned *from, size_t fromPos, unsigned int *to, size_t length) {
    for(size_t i = fromPos; i < fromPos + length; ++i) {
        to[i] = from[i];
    }
}
