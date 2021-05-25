#include "number.h"
#include "utils.h"
#include "multiplication.h"
#include "tables.h"

Number columnMultiply(const Number &x, const Number &y) {
    if (x.getN() < y.getN()) {
        return columnMultiply(y, x);
    }

    uint32_t xSize = x.getN(), ySize = y.getN();
    uint32_t size = xSize + ySize;
    const Array &xArr = x.getArray();
    const Array &yArr = y.getArray();

    auto *array = new uint8_t[size];
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

    size_t newSize = max(1, getNormalizedLength(size, array));
    Array arr(newSize, array);
    Number n(x.isNegative() ^ y.isNegative(), arr);
    delete[] array;
    return n;
}

Number shift(const Number &n, uint32_t digits) {
    const Array& arr = n.getArray();
    if (arr.getSize() == 1 && arr[0] == 0) return n;
    Array outArr(arr.getSize() + digits);
    for (uint32_t i = 0; i < digits; ++i) {
        outArr.add(0);
    }
    for (uint32_t i = 0; i < arr.getSize(); ++i) {
        outArr.add(arr[i]);
    }
    return Number(n.isNegative(), std::move(outArr));
}

Number karatsubaMultiply(const Number &x, const Number &y) {
    uint32_t n = max(x.getN(), y.getN());
    if (n <= 4) {
        return columnMultiply(x, y);
    }

    if (n % 2 != 0) ++n;

    uint32_t nHalf = n >> 1;
    
    const Array &xArr = x.getArray();
    const Array &yArr = y.getArray();
    uint32_t xSize = xArr.getSize();
    uint32_t ySize = yArr.getSize();
    
    Array a1, b1, c1, d1;
    for (uint32_t i = 0; i < nHalf; ++i) {
        if (i < xSize) b1.add(xArr[i]);
        if (i < ySize) d1.add(yArr[i]);
    }
    for (uint32_t i = nHalf; i < n; ++i) {
        if (i < xSize) a1.add(xArr[i]);
        if (i < ySize) c1.add(yArr[i]);
    }
    if (a1.getSize() == 0) a1.add(0);
    if (b1.getSize() == 0) b1.add(0);
    if (c1.getSize() == 0) c1.add(0);
    if (d1.getSize() == 0) d1.add(0);
    Number
        a(false, std::move(a1)),
        b(false, std::move(b1)),
        c(false, std::move(c1)),
        d(false, std::move(d1));
    Number u = karatsubaMultiply(a + b, c + d);
    Number v = karatsubaMultiply(a, c);
    Number w = karatsubaMultiply(b, d);

    return shift(v, n) + shift(u - v - w, nHalf) + w;
}
