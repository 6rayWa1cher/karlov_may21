//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#ifndef KARLOV_MAY21_NUMBER_H
#define KARLOV_MAY21_NUMBER_H

#include <iostream>
#include "array.h"

/*
 * FORMAT
 * if input == 0xABCD and sizeof(int) == 1
 * array[0] = 0xCD, array[1] = 0xAB
 */
class Number {
private:
    Array array;
    bool negative;
public:
    Number();

    Number(bool negative, const Array &array);

    Number(bool negative, Array&& array);

    explicit Number(const char *str);

    size_t getN() const;

    const Array &getArray() const;

    bool isNegative() const;

    explicit operator std::string() const {
        return toString();
    }

    std::string toString() const;

    bool operator<(const Number &rhs) const;

    bool operator>(const Number &rhs) const;

    bool operator<=(const Number &rhs) const;

    bool operator>=(const Number &rhs) const;
};

std::ostream& operator<<(std::ostream& ostream, const Number &n);

Number operator+(const Number &n1, const Number &n2);

Number operator-(const Number &n1, const Number &n2);

bool operator==(const Number &n1, const Number &n2);

bool operator!=(const Number &n1, const Number &n2);

#endif //KARLOV_MAY21_NUMBER_H
