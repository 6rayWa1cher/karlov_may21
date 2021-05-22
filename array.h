//
// Created by 6rayWa1cher on 22-May-21.
//

#ifndef KARLOV_MAY21_ARRAY_H
#define KARLOV_MAY21_ARRAY_H

#include <iostream>

class Array {
private:
    uint8_t *arr;
    uint32_t size;
    uint32_t capacity;
public:
    Array();

    explicit Array(uint32_t initialCapacity);

    Array(uint32_t size, uint8_t *arr);

    Array(const Array& x); // copy constructor

    Array(Array&& x) noexcept; // move constructor

    Array& operator=(const Array& rhs); // copy assignment

    Array& operator=(Array&& rhs) noexcept; // move assignment

    uint8_t add(uint8_t v);

    uint8_t operator[](uint32_t i) const;

    uint8_t get(uint32_t i) const;

    void replace(uint32_t i, uint8_t v);

    uint32_t getSize() const;

    void removeByIndex(uint32_t i);

    std::string toString() const;

    uint32_t getCapacity() const;

    ~Array();
};

bool operator==(const Array& a, const Array& b);
bool operator!=(const Array& a, const Array& b);

#endif //KARLOV_MAY21_ARRAY_H
