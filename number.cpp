//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#include "number.h"
#include "utils.h"
#include "config.h"

Number::Number(bool negative, size_t n, const unsigned *arr) : n(n), negative(negative) {
    array = new unsigned[n];
    copy((unsigned *) arr, 0, array, n);
}

Number::~Number() {
    delete array;
}

int Number::getN() const {
    return n;
}

unsigned *Number::getArray() const {
    return array;
}

bool Number::isNegative() const {
    return negative;
}

unsigned long toInt(const char* str, size_t from, size_t to) {
    unsigned long out = 0;
    for (size_t i = from; i < to; ++i) {
        out = out * 10 + (unsigned long) (str[i] - '0');
    }
    return out;
}

Number::Number(const char *str) {
    negative = str[0] == '-';
    bool signPresented = str[0] == '+' || str[0] == '-';
    size_t strN = 0;
    while (str[strN] != '\0') ++strN;

    n = 10;
    array = new unsigned[n];
    unsigned long prevBuf, buf;
    size_t ptr = 0;
    size_t prevPosition = strN;
    for(size_t i = strN; i > 0;) {
        size_t actualPointer = i - 1;
        if (signPresented && actualPointer == 0) break;
        prevBuf = buf;
        buf = toInt(str, actualPointer, prevPosition);
        if (buf > BASE) {
            array[ptr++] = prevBuf;
            prevPosition = actualPointer + 1;
            buf = buf / BASE;
            if (ptr >= n){
                doubleArraySize(n, array);
                n *= 2;
            }
        } else {
            --i;
        }
    }
    array[ptr++] = toInt(str, signPresented ? 1 : 0, prevPosition);
    if (ptr >= n){
        doubleArraySize(n, array);
        n *= 2;
    }
    n = eraseEndingZeroes(n, array);
}

