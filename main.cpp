#include <iostream>
#include <math.h>
#include "number.h"
#include "utils.h"
#include "config.h"


Number columnMultiply(Number *x, Number *y) {
    if (x->getN() < y->getN()) {
        Number *t = x;
        x = y;
        y = t;
    }
    size_t xSize = x->getN(), ySize = y->getN();
    size_t size = xSize + ySize;
    unsigned *xArr = x->getArray();
    unsigned *yArr = y->getArray();

    unsigned out[size];
    for (size_t i = 0; i < size; ++i) out[i] = 0;

    unsigned long upperPart, lowerPart, resultPart;
    unsigned carry;
    for (size_t i = 0; i < ySize; ++i) {
        lowerPart = yArr[i];
        carry = 0;
        for (size_t j = 0; j < xSize; ++j) {
            upperPart = xArr[j];
            resultPart = lowerPart * upperPart + carry + out[j + i];
            carry = resultPart / BASE;
            out[j + i] = resultPart % BASE;
        }
        if (carry != 0) {
            out[xSize + i] = carry;
        }
    }

    size_t newSize = eraseEndingZeroes(size, out);
    return Number(x->isNegative() ^ y->isNegative(), newSize, out);
}

Number _$karatsubaMultiply(Number* x, size_t xFrom, size_t xTo, Number* y, size_t yFrom, size_t yTo) {

}

Number karatsubaMultiply(Number* x, Number* y) {

}

int main() {
    unsigned arr1[]{
            5, 4
    };
    unsigned arr2[]{
            7, 2
    };
    Number n1(false, 2, arr1);
    Number n2(false, 2, arr2);
    Number n3 = columnMultiply(&n1, &n2);
    // 1215 in base 10,
    // 3,8,10 === A83 in base 16
    unsigned int *pInt = n3.getArray();
    std::cout << (n3.isNegative() ? "-" : "+") << n3.getN() << std::endl;
    for (size_t i = 0; i < n3.getN(); ++i) {
        std::cout << pInt[i];
        if (i + 1 != n3.getN()) {
            std::cout << ",";
        }
    }
}
