//
// Created by 6rayWa1cher on 22-May-21.
//

#include "array.h"
#include "utils.h"
#include <string>
#include <sstream>

Array::Array() : Array(10) {

}

Array::Array(uint32_t initialCapacity) : size(0), capacity(initialCapacity) {
    arr = new uint8_t[initialCapacity];
}


Array::Array(uint32_t size, uint8_t *rarr) : size(size), capacity(size) {
    arr = new uint8_t[size];
    copy((uint8_t *) rarr, 0, arr, 0, size);
}

uint32_t Array::getSize() const {
    return size;
}

uint8_t Array::add(uint8_t v) {
    if (size == capacity) {
        auto* newArr = new uint8_t[capacity << 1];
        copy((uint8_t *) arr, 0, newArr, 0, size);
        delete[] arr;
        arr = newArr;
        capacity = capacity << 1;
    }
    arr[size++] = v;
    return v;
}

uint8_t Array::get(uint32_t i) const {
    if (i < 0 || i >= size) {
        throw "Out of bound: " + std::to_string(i) + " of size " + std::to_string(size);
    }
    return arr[i];
}

void Array::replace(uint32_t i, uint8_t v) {
    if (i < 0 || i >= size) {
        throw "Out of bound: " + std::to_string(i) + " of size " + std::to_string(size);
    }
    arr[i] = v;
}

uint8_t Array::operator[](uint32_t i) const {
    if (i < 0 || i >= size) {
        throw "Out of bound: " + std::to_string(i) + " of size " + std::to_string(size);
    }
    return arr[i];
}

void Array::removeByIndex(uint32_t i) {
    if (i < 0 || i >= size) {
        throw "Out of bound: " + std::to_string(i) + " of size " + std::to_string(size);
    }
    if (size <= capacity >> 2 && capacity >> 2 >= 10) {
        auto* newArr = new uint8_t[capacity >> 2];
        copy((uint8_t *) arr, 0, newArr, 0, size);
        delete[] arr;
        arr = newArr;
        capacity = capacity >> 2;
    }
    if (i + 1 == size) {
        --size;
    } else {
        copy((uint8_t *) arr, i + 1, arr, i, size - i - 1);
        --size;
    }
}

Array::~Array() {
    delete[] arr;
}

std::string Array::toString() const{
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

Array &Array::operator=(const Array &rhs) {
    if (&rhs != this) {
        auto* newArray = new uint8_t[rhs.capacity];
        copy((uint8_t *) rhs.arr, 0, newArray, 0, rhs.size);
        delete[] arr;
        arr = newArray;
        size = rhs.size;
        capacity = rhs.capacity;
    }
    return *this;
}

Array::Array(const Array &x) : size(x.size), capacity(x.capacity),
    arr(new uint8_t[x.capacity]){
    copy((uint8_t *) x.arr, 0, arr, 0, x.size);
}

Array &Array::operator=(Array&& rhs) noexcept {
    delete[] arr;
    arr = rhs.arr;
    size = rhs.size;
    capacity = rhs.capacity;

    rhs.arr = new uint8_t[10];
    rhs.size = 0;
    rhs.capacity = 10;
    return *this;
}

Array::Array(Array &&x) noexcept : size(x.size), capacity(x.capacity),
                          arr(x.arr) {
    x.arr = new uint8_t[10];
    x.size = 0;
    x.capacity = 10;
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