//
// Created by Konstantin Grigoriev on 03.05.2021.
//

#ifndef KARLOV_MAY21_UTILS_H
#define KARLOV_MAY21_UTILS_H

#include <iostream>

size_t getNormalizedLength(size_t n, const uint8_t* arr);

void copy(const uint8_t *from, size_t fromPos, uint8_t *to, size_t toPos, size_t length);

void copy(const uint8_t *from, uint8_t* to, size_t length);

uint8_t *clone(const uint8_t *from, size_t capacity, size_t dataSize);

uint8_t *clone(const uint8_t *from, size_t size);

size_t max(size_t i, size_t j);

size_t min(size_t i, size_t j);

#endif //KARLOV_MAY21_UTILS_H
