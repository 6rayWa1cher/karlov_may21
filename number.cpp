//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#include <sstream>
#include <cassert>
#include "number.h"
#include "utils.h"
#include "tables.h"

Number::Number(bool negative, const Array& array) : negative(negative), array(array) {

}

size_t Number::getN() const {
    return array.getSize();
}

bool Number::isNegative() const {
    return negative;
}

Number::Number(const char *str) {
    negative = str[0] == '-';
    bool signPresented = str[0] == '+' || str[0] == '-';

    uint32_t strN = 0;
    while (str[strN] != '\0') ++strN;

    array = Array(strN);

    for (int64_t i = strN - 1; i >= (int) signPresented; --i) {
        array.add(str[i] - '0');
    }
}

const Array& Number::getArray() const {
    return array;
}

Number::Number() : negative(false), array(1) {
    array.add(0);
}

Array sumNumbers(const Number &in1, const Number &in2) {
    const Number& n1 = in1.getN() <= in2.getN() ? in2 : in1;
    const Number& n2 = in1.getN() <= in2.getN() ? in1 : in2;

    Array array(max(n1.getN(), n2.getN()) + 1);
    bool carry = false;

    const Array &n1a = n1.getArray();
    const Array &n2a = n2.getArray();

    for (uint32_t i = 0; i < n1.getN(); ++i) {

        uint8_t sum = n1a[i] + carry;
        if (i < n2.getN()) sum += + n2a[i];

        if (sum >= 10) {
            array.add(sum - 10);
            carry = true;
        } else {
            array.add(sum);
            carry = false;
        }
    }

    if (carry) {
        array.add(1);
    }

    return array;
}

Array subNumbers(const Number &in1, const Number &in2) {
    Array array(max(in1.getN(), in2.getN()) + 1);
    bool carry = false;

    const Array &n1a = in1.getArray();
    const Array &n2a = in2.getArray();

    for (uint32_t i = 0; i < in1.getN(); ++i) {

        int8_t sub = n1a[i] - carry;
        if (i < in2.getN()) sub -= n2a[i];

        if (sub < 0) {
            array.add(sub + 10);
            carry = true;
        } else {
            array.add(sub);
            carry = false;
        }
    }

    for (int64_t i = array.getSize() - 1; i >= 0; --i) {
        if (array[i] == 0 && i != 0) {
            array.removeByIndex(i);
        } else {
            break;
        }
    }

    return array;
}

Number operator+(const Number &in1, const Number &in2) {
    Array array = sumNumbers(in1, in2);

    return Number(false, array);
}

bool operator==(const Number &n1, const Number &n2) {
    if (n1.isNegative() != n2.isNegative()) return false;

    return n1.getArray() == n2.getArray();
}

bool operator!=(const Number &n1, const Number &n2) {
    return !(n1 == n2);
}

std::ostream& operator<<(std::ostream& ostream, const Number &n) {
    if (n.isNegative()) {
        ostream << "-";
    }

    const Array &array = n.getArray();

    for (auto i = (int64_t) n.getN() - 1; i >= 0; --i) {
        ostream << (int) array[i];
    }

    return ostream;
}

Number operator-(const Number &in1, const Number &in2) {
    Array array = subNumbers(in1, in2);

    return Number(false, array);
}

bool Number::operator<(const Number &rhs) const {
    if (negative && !rhs.negative) return true;
    if (!negative && rhs.negative) return false;

    if (getN() < rhs.getN()) return true;
    if (getN() > rhs.getN()) return false;

    const Array &rhsArray = rhs.getArray();

    for (auto i = (int64_t) getN() - 1; i >= 0; --i) {
        if (array[i] < rhsArray[i]) return true;
    }

    return false;
}

bool Number::operator>(const Number &rhs) const {
    return rhs < *this;
}

bool Number::operator<=(const Number &rhs) const {
    return !(rhs < *this);
}

bool Number::operator>=(const Number &rhs) const {
    return !(*this < rhs);
}

std::string Number::toString() const {
    std::ostringstream oss;

    oss << *this;

    return oss.str();
}

Number::Number(bool negative, Array &&array) : negative(negative), array(array) {

}