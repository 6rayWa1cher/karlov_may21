#include <iostream>
#include <math.h>
#include "number.h"
#include "utils.h"
#include "array.h"

uint8_t multiplicationTable[10][10] = {
        {0, 0, 0,  0,  0,  0,  0,  0,  0,  0},
        {0, 1, 2,  3,  4,  5,  6,  7,  8,  9},
        {0, 2, 4,  6,  8,  10, 12, 14, 16, 18},
        {0, 3, 6,  9,  12, 15, 18, 21, 24, 27},
        {0, 4, 8,  12, 16, 20, 24, 28, 32, 36},
        {0, 5, 10, 15, 20, 25, 30, 35, 40, 45},
        {0, 6, 12, 18, 24, 30, 36, 42, 48, 54},
        {0, 7, 14, 21, 28, 35, 42, 49, 56, 63},
        {0, 8, 16, 24, 32, 40, 48, 56, 64, 72},
        {0, 9, 18, 27, 36, 45, 54, 63, 72, 81}
};

uint8_t modTable[256] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1,
                         2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3,
                         4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5,
                         6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7,
                         8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                         0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1,
                         2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3,
                         4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4,
                         5};

uint8_t divTable[256] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3,
                         3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6,
                         6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9,
                         9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,
                         12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14,
                         14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16,
                         16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19,
                         19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21,
                         21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24,
                         24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25};

Number columnMultiply(const Number &a, const Number &b) {
    Number x, y;
    if (a.getN() < b.getN()) {
        x = b;
        y = a;
    } else {
        x = a;
        y = b;
    }

    uint32_t xSize = x.getN(), ySize = y.getN();
    uint32_t size = xSize + ySize;
    const Array &xArr = x.getArray();
    const Array &yArr = y.getArray();

    auto* array = new uint8_t[size];
    for (size_t i = 0; i < size; ++i) array[i] = 0;

    uint8_t upperPart, lowerPart, resultPart, carry;
    for (uint32_t i = 0; i < ySize; ++i) {
        lowerPart = yArr[i];
        carry = 0;
        for (size_t j = 0; j < xSize; ++j) {
            upperPart = xArr[j];
            resultPart = multiplicationTable[lowerPart][upperPart]
                         + carry + array[j + i];
            carry = divTable[resultPart];
            array[j + i] = modTable[resultPart];
        }
        if (carry != 0) {
            array[xSize + i] = carry;
        }
    }

    size_t newSize = eraseEndingZeroes(size, array);
    Array arr(newSize, array);
    Number n(x.isNegative() ^ y.isNegative(), arr);
    delete[] array;
    std::cout << n << std::endl;
    return n;
}

//Number columnMultiply(Number *x, Number *y) {
//    if (x->getN() < y->getN()) {
//        Number *t = x;
//        x = y;
//        y = t;
//    }
//    size_t xSize = x->getN(), ySize = y->getN();
//    size_t size = xSize + ySize;
//    uint8_t *xArr = x->getArray();
//    uint8_t *yArr = y->getArray();
//
//    uint8_t* out = new uint8_t[size];
//    for (size_t i = 0; i < size; ++i) out[i] = 0;
//
//    unsigned long upperPart, lowerPart, resultPart;
//    unsigned carry;
//    for (size_t i = 0; i < ySize; ++i) {
//        lowerPart = yArr[i];
//        carry = 0;
//        for (size_t j = 0; j < xSize; ++j) {
//            upperPart = xArr[j];
//            resultPart = lowerPart * upperPart + carry + out[j + i];
//            carry = resultPart / BASE;
//            out[j + i] = resultPart % BASE;
//        }
//        if (carry != 0) {
//            out[xSize + i] = carry;
//        }
//    }
//
//    size_t newSize = eraseEndingZeroes(size, out);
//    Number n(x->isNegative() ^ y->isNegative(), newSize, out);
//    delete[] out;
//    return n;
//}
//
//Number _$karatsubaMultiply(Number* x, size_t xFrom, size_t xTo, Number* y, size_t yFrom, size_t yTo) {
//
//}
//
//Number karatsubaMultiply(Number* x, Number* y) {
//
//}

void testArray() {
    Array a;
    for (int i = 0; i < 20; ++i) {
        a.add(i);
    }
    std::cout << a.getCapacity() << std::endl;
    a.add(2);
    std::cout << a.toString() << std::endl;
    std::cout << a.getCapacity() << std::endl;
    a.add(23);
    std::cout << a.toString() << std::endl;
    a.add(79);
    std::cout << a.toString() << std::endl;
    a.replace(1, 8);
    std::cout << a.toString() << std::endl;
    std::cout << a.getCapacity() << std::endl;
    for (int i = 0; i < 17; ++i) {
        a.removeByIndex(1);
    }
    std::cout << a.toString() << std::endl;
    std::cout << a.getCapacity() << std::endl;
    {
        Array b = a;
        std::cout << (a == b) << std::endl;
        b.add(1);
        std::cout << b.toString() << std::endl;
        std::cout << b.getCapacity() << std::endl;
        std::cout << (a == b) << std::endl;
    }
}

int main() {
//    uint8_t arr1[]{
//            5, 4
//    };
//    uint8_t arr2[]{
//            7, 2
//    };
    Number n1("45");
    Number n2("27");
//    Array a(2);
//    a.add(7);
//    a.add(2);
    std::cout << n1.getArray().toString() << std::endl;
    std::cout << n2.getArray().toString() << std::endl;
    std::cout << n1 << std::endl;
    std::cout << n2 << std::endl;
//    std::cout << a.toString() << std::endl;
    Number n3 = columnMultiply(n1, n2);
    // 1215 in base 10,
    // 3,8,10 === A83 in base 16
    std::cout << n3 << std::endl;
//    uint8_t *pInt = n3.getArray();
//    std::cout << (n3.isNegative() ? "-" : "+") << n3.getN() << std::endl;
//    for (size_t i = 0; i < n3.getN(); ++i) {
//        std::cout << pInt[i];
//        if (i + 1 != n3.getN()) {
//            std::cout << ",";
//        }
//    }
//    testArray();
}

