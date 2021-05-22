#include <iostream>
#include "number.h"
#include "multiplication.h"

int main() {
    Number n1("45");
    Number n2("27");
    std::cout << n1.getArray().toString() << std::endl;
    std::cout << n2.getArray().toString() << std::endl;
    std::cout << n1 << std::endl;
    std::cout << n2 << std::endl;
//    std::cout << a.toString() << std::endl;
    Number n3 = columnMultiply(n1, n2);
    // 1215 in base 10,
    // 3,8,10 === A83 in base 16
    std::cout << n3 << std::endl;
//    uint8_t *pInt = n3.getArray();
//    std::cout << (n3.isNegative() ? "-" : "+") << n3.getN() << std::endl;
//    for (size_t i = 0; i < n3.getN(); ++i) {
//        std::cout << pInt[i];
//        if (i + 1 != n3.getN()) {
//            std::cout << ",";
//        }
//    }
//    testArray();
}

