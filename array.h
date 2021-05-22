//
// Created by 6rayWa1cher on 22-May-21.
//

#ifndef KARLOV_MAY21_ARRAY_H
#define KARLOV_MAY21_ARRAY_H

#include <iostream>
#include <string>

class Array {
private:
    uint8_t *arr;
    uint32_t size;
    uint32_t capacity;
public:
    Array();

    explicit Array(uint32_t initialCapacity);

    Array(uint32_t size, uint8_t *inpArr);

    Array(const Array& x); // copy constructor

    Array& operator=(const Array& rhs); // copy assignment

    uint8_t add(uint8_t v);

    uint8_t& operator[](uint32_t i) const;

    uint8_t at(uint32_t i) const;

    uint32_t getSize() const;

    void removeByIndex(uint32_t i);

    std::string toString() const;

    uint32_t getCapacity() const;

    ~Array();

private:
    void assertBound(uint32_t i) const;
};

bool operator==(const Array& a, const Array& b);

bool operator!=(const Array& a, const Array& b);

#endif //KARLOV_MAY21_ARRAY_H
