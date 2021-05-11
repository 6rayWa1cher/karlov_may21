//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#ifndef KARLOV_MAY21_NUMBER_H
#define KARLOV_MAY21_NUMBER_H

#include <iostream>

/*
 * FORMAT
 * if input == 0xABCD and sizeof(int) == 1
 * array[0] = 0xCD, array[1] = 0xAB
 */
class Number {
private:
    size_t n;
    unsigned *array;
    bool negative;
    bool owns = true;
public:
    Number(bool negative, size_t n, const unsigned *arr);

    Number(bool negative, size_t n, const unsigned *arr, bool copy, bool owns);

    explicit Number(const char *str);

    ~Number();

    int getN() const;

    unsigned *getArray() const;

    bool isNegative() const;
};

Number operator+(Number& n1, Number& n2);

#endif //KARLOV_MAY21_NUMBER_H
