//
// Created by 6rayWa1cher on 22-May-21.
//

#include "array.h"
#include "utils.h"
#include <string>
#include <sstream>

Array::Array() : Array(10) {

}

Array::Array(uint32_t initialCapacity) : size(0), capacity(initialCapacity),
                                         arr(new uint8_t[initialCapacity]) {

}


Array::Array(uint32_t size, uint8_t *inpArr) : size(size), capacity(size),
                                               arr(clone(inpArr, size)) {

}

Array::Array(const Array &x) : size(x.size), capacity(x.capacity),
                               arr(clone(x.arr, x.size, x.capacity)) {

}

Array &Array::operator=(const Array &rhs) {
    if (&rhs != this) {
        auto *newArray = clone(rhs.arr, rhs.size, rhs.capacity);

        delete[] arr;
        arr = newArray;

        size = rhs.size;
        capacity = rhs.capacity;
    }
    return *this;
}

uint8_t Array::add(uint8_t v) {
    if (size == capacity) {
        uint32_t extendedCapacity = capacity << 1;
        auto *newArr = clone(arr, size, extendedCapacity);

        delete[] arr;
        arr = newArr;

        capacity = extendedCapacity;
    }

    arr[size++] = v;

    return v;
}

uint8_t &Array::operator[](uint32_t i) const {
    return arr[i];
}

uint8_t Array::at(uint32_t i) const {
    assertBound(i);

    return arr[i];
}

uint32_t Array::getSize() const {
    return size;
}

void Array::removeByIndex(uint32_t i) {
    assertBound(i);

    uint32_t reducedCapacity = capacity >> 2;
    if (reducedCapacity >= size && reducedCapacity >= 10) {
        auto *newArray = clone(arr, size, reducedCapacity);

        delete[] arr;
        arr = newArray;

        capacity = reducedCapacity;
    }

    if (i + 1 != size) {
        copy((uint8_t *) arr, i + 1, arr, i, size - i - 1);
    }

    --size;
}


std::string Array::toString() const {
    std::ostringstream oss;

    for (int i = 0; i < size; ++i) {
        oss << (int) arr[i];
        if (i != size - 1) {
            oss << ',';
        }
    }

    return oss.str();
}

uint32_t Array::getCapacity() const {
    return capacity;
}

Array::~Array() {
    delete[] arr;
}

void Array::assertBound(uint32_t i) const {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Out of bound: " + std::to_string(i) + " of size " + std::to_string(size));
    }
}

Array::Array(uint32_t size, uint8_t *inpArr, bool cloneArr) :
        size(size), capacity(size), arr(cloneArr ? clone(inpArr, size) : inpArr) {

}

Array::Array(Array && a) noexcept : arr(a.arr), size(a.size), capacity(a.capacity){
    a.size = 0;
    a.capacity = 0;
    a.arr = nullptr;
}

bool operator==(const Array &a, const Array &b) {
    if (a.getSize() != b.getSize()) return false;

    for (int i = 0; i < a.getSize(); ++i) {
        if (a[i] != b[i]) return false;
    }

    return true;
}

bool operator!=(const Array &a, const Array &b) {
    return !(a == b);
}