//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#include "utils.h"

void doubleArraySize(size_t n, uint8_t *&arr) {
    auto *out = new uint8_t[n * 2];
    for (size_t i = 0; i < n; ++i) {
        out[i] = arr[i];
    }
    delete arr;
    arr = out;
}

uint8_t *copyDoubleArraySize(size_t n, uint8_t *arr) {
    auto *out = new uint8_t[n * 2];
    for (size_t i = 0; i < n; ++i) {
        out[i] = arr[i];
    }
    return out;
}

size_t eraseEndingZeroes(size_t n, uint8_t *arr) {
    size_t nonTailLength = n;
    while (nonTailLength != 0 && arr[nonTailLength - 1] == 0) --nonTailLength;
    auto *out = new uint8_t[nonTailLength];
    copy(arr, 0, out, 0, nonTailLength);
    return nonTailLength;
}

void copy(const uint8_t *from, size_t fromPos, uint8_t *to, size_t toPos, size_t length) {
//    for (size_t i = fromPos; i < fromPos + length; ++i) {
//        to[i] = from[i];
//    }
    size_t i = fromPos;
    size_t j = toPos;
    for (int k = 0; k < length; ++k) {
        to[j++] = from[i++];
    }
}

size_t max(size_t i, size_t j) {
    return i < j ? j : i;
}

size_t min(size_t i, size_t j) {
    return i < j ? i : j;
}
