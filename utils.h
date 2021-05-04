//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#ifndef KARLOV_MAY21_UTILS_H
#define KARLOV_MAY21_UTILS_H

#include <iostream>

void doubleArraySize(size_t n, unsigned *&arr);

unsigned * copyDoubleArraySize(size_t n, unsigned *arr);

size_t eraseEndingZeroes(size_t n, unsigned* arr);

void copy(const unsigned *from, size_t fromPos, unsigned *to, size_t length);

#endif //KARLOV_MAY21_UTILS_H
