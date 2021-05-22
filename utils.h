//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#ifndef KARLOV_MAY21_UTILS_H
#define KARLOV_MAY21_UTILS_H

#include <iostream>

void doubleArraySize(size_t n, uint8_t *&arr);

uint8_t * copyDoubleArraySize(size_t n, uint8_t *arr);

size_t eraseEndingZeroes(size_t n, uint8_t* arr);

void copy(const uint8_t *from, size_t fromPos, uint8_t *to, size_t toPos, size_t length);

size_t max(size_t i, size_t j);

size_t min(size_t i, size_t j);

#endif //KARLOV_MAY21_UTILS_H
