//
// Created by 6rayWa1cher on 22-May-21.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch2/catch.hpp"
#include "array.h"
#include <iostream>

TEST_CASE("The most needed Array functions", "[array]") {
    Array a;
    for (int i = 0; i < 20; ++i) {
        a.add(i);
    }
    REQUIRE(a.getCapacity() == 40);
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