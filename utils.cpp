//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#include "utils.h"


size_t getNormalizedLength(size_t n, const uint8_t *arr) {
    size_t nonTailLength = n;
    while (nonTailLength != 0 && arr[nonTailLength - 1] == 0) --nonTailLength;
    return nonTailLength;
}

void copy(const uint8_t *from, size_t fromPos, uint8_t *to, size_t toPos, size_t length) {
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

void copy(const uint8_t *from, uint8_t *to, size_t length) {
    copy(from, 0, to, 0, length);
}

uint8_t *clone(const uint8_t *from, size_t dataSize) {
    return clone(from, dataSize, dataSize);
}

uint8_t *clone(const uint8_t *from, size_t dataSize, size_t capacity) {
    auto* newArr = new uint8_t[capacity];
    copy((uint8_t *) from, newArr, dataSize);
    return newArr;
}
