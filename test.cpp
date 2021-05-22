//
// Created by 6rayWa1cher on 22-May-21.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "catch2/catch.hpp"
#include "array.h"
#include "number.h"
#include "multiplication.h"
#include <iostream>

namespace Catch {
    template<>
    struct StringMaker<Number> {
        static std::string convert(Number const &s) {
            return s.toString();
        }
    };

    template<>
    struct StringMaker<Array> {
        static std::string convert(Array const &s) {
            return s.toString();
        }
    };
}


TEST_CASE("The most needed Array functions", "[array]") {
    Array a;
    for (int i = 0; i < 20; ++i) {
        a.add(i);
    }
    REQUIRE(a.getCapacity() == 20);
    a.add(2);
    REQUIRE(a.toString() == "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,2");
    REQUIRE(a.getCapacity() == 40);
    a.add(23);
    a.add(79);
    REQUIRE(a.toString() == "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,2,23,79");
    a[1] = 8;
    REQUIRE(a.toString() == "0,8,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,2,23,79");
    REQUIRE(a.getCapacity() == 40);
    for (int i = 0; i < 17; ++i) {
        a.removeByIndex(1);
    }
    REQUIRE(a.toString() == "0,18,19,2,23,79");
    REQUIRE(a.getCapacity() == 10);
    {
        Array b = a;
        REQUIRE(a == b);
        REQUIRE(&a != &b);
        REQUIRE(&a[0] != &b[0]);
        b.add(1);
        REQUIRE(b.toString() == "0,18,19,2,23,79,1");
        REQUIRE(b.getCapacity() == 10);
        REQUIRE(a != b);
    }
}

TEST_CASE("Number simple tests", "[number]") {
    Number n1("43");
    REQUIRE(n1.toString() == "43");
    REQUIRE(n1.getArray() == Array(2, new uint8_t[]{3, 4}));
    Number n2("99");
    Number n3 = n1 + n2;
    REQUIRE(n3.toString() == "142");
    REQUIRE(n3.getArray() == Array(3, new uint8_t[]{2, 4, 1}));
    REQUIRE(n3 == Number("142"));
    Number nn("-14");
    REQUIRE(nn.toString() == "-14");
    REQUIRE(nn.getArray() == Array(2, new uint8_t[]{4, 1}));
    REQUIRE(nn.isNegative());
    REQUIRE(n1 < n2);
    REQUIRE(nn < n1);
    REQUIRE(n1 < n3);
}

TEST_CASE("Number multiplication test by column method", "[number][columnmult]") {
    {
        Number n1("45");
        Number n2("27");
        REQUIRE(columnMultiply(n1, n2) == Number("1215"));
    }
    {
        Number n1("-45");
        Number n2("27");
        REQUIRE(columnMultiply(n1, n2) == Number("-1215"));
    }
    {
        Number n1("-45");
        Number n2("-27");
        REQUIRE(columnMultiply(n1, n2) == Number("1215"));
    }
    {
        Number n1("45");
        Number n2("2");
        REQUIRE(columnMultiply(n1, n2) == Number("90"));
    }
    {
        Number n1("4");
        Number n2("23");
        REQUIRE(columnMultiply(n1, n2) == Number("92"));
    }
    {
        Number n1("0");
        Number n2("23");
        Number n3 = columnMultiply(n1, n2);
        REQUIRE(n3 == Number("0"));
        REQUIRE(n3.getArray().getSize() == 1);
        REQUIRE(n3.toString() == "0");
    }
}