//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#include <sstream>
#include "number.h"
#include "utils.h"

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

Array sumNumbers(Number &in1, Number &in2) {
    Number& n1 = in1.getN() <= in2.getN() ? in2 : in1;
    Number& n2 = in1.getN() <= in2.getN() ? in1 : in2;
    Array array(max(n1.getN(), n2.getN()) + 1);
    bool carry = false;
    const Array &n1a = n1.getArray();
    const Array &n2a = n2.getArray();
    for (uint32_t i = 0; i < n2.getN(); ++i) {
        uint8_t sum = n1a[i] + n2a[i] + carry;
        if (sum >= 10) {
            array.add(sum - 10);
            carry = true;
        } else {
            array.add(sum);
            carry = false;
        }
    }
    for (uint32_t i = n2.getN(); i < n1.getN(); ++i) {
        uint8_t sum = n1a[i] + carry;
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
//
//Array subNumbers(Number &in1, Number &in2) {
//    if (in1 == in2) {
//        Array array;
//        array.add(0);
//        return array;
//    }
//    Number& n1 = in1 < in2 ? in2 : in1;
//    Number& n2 = in1 < in2 ? in1 : in2;
//    Array array(max(n1.getN(), n2.getN()));
//    bool carry = false;
//    const Array &n1a = n1.getArray();
//    const Array &n2a = n2.getArray();
//    for (uint32_t i = 0; i < n2.getN(); ++i) {
//        uint8_t subPart = n2a[i] + carry;
//        if (n1a[i] < subPart) {
//            array.add(10 + n1a[i] - subPart);
//            carry = true;
//        } else {
//            array.add(n1a[i] - subPart);
//            carry = false;
//        }
//    }
//    for (uint32_t i = n2.getN(); i < n1.getN(); ++i) {
//        if (carry) {
//            if (n1a[i] == 0) {
//                array.add(9);
//                carry = true;
//            } else {
//                array.add(n1a[i] - 1);
//                carry = false;
//            }
//        } else {
//            array.add(n1a[i]);
//        }
//    }
//    for (int64_t i = array.getSize(); i >= 0; --i) {
//        if (array[i] == 0) {
//            array.removeByIndex(i);
//        }
//    }
//    if (carry) {
//        array.add(1);
//    }
//}

Number operator+(Number &in1, Number &in2) {
    Array array = sumNumbers(in1, in2);
    return Number(false, array);
//    bool in1Neg = in1.isNegative();
//    bool in2Neg = in2.isNegative();
//    if (in1Neg && in2Neg) {
//        Array array = sumNumbers(in1, in2);
//        return Number(true, array);
//    } else if (!in1Neg && !in2Neg) {
//        Array array = sumNumbers(in1, in2);
//        return Number(false, array);
//    }
}

//Number operator-(Number &in1, Number &in2) {
//    Array array = sumNumbers(in1, in2);
//    return Number(!(in1.isNegative() ^ in2.isNegative()), array);
//}

bool operator==(Number &n1, Number &n2) {
    if (n1.isNegative() != n2.isNegative()) return false;
    return n1.getArray() == n2.getArray();
}

bool operator!=(Number &n1, Number &n2) {
    return !(n1 == n2);
}

std::ostream& operator<<(std::ostream& ostream, const Number &n) {
    if (n.isNegative()) {
        ostream << "-";
    }
    const Array &array = n.getArray();
    for (int64_t i = n.getN() - 1; i >= 0; --i) {
        ostream << (int) array[i];
    }
    return ostream;
}

bool Number::operator<(const Number &rhs) const {
    if (negative && !rhs.negative) return true;
    if (!negative && rhs.negative) return false;
    if (getN() < rhs.getN()) return true;
    if (getN() > rhs.getN()) return false;
    const Array &rhsArray = rhs.getArray();
    for (int64_t i = getN() - 1; i >= 0; --i) {
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
