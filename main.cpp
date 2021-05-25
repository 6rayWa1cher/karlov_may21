#include <iostream>
#include <fstream>
#include <ctime>
#include <ratio>
#include <chrono>
#include "number.h"
#include "multiplication.h"

using namespace std::chrono;
using namespace std;

static bool printAnswer = false;
static int timesOfBench = 2;

struct BenchResults {
    double columnResult = 0;

    Number sampleColumnAnswer;

    double karatsubaResult = 0;

    Number sampleKaratsubaAnswer;
};

BenchResults bench(const Number& x, const Number& y, int times) {
    BenchResults benchResults;
    for (int i = 0; i < times; ++i) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        benchResults.sampleColumnAnswer = columnMultiply(x, y);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double, std::milli> d = t2 - t1;
        benchResults.columnResult += d.count();
        cout << "Made column " << d.count() << "ms, " << (i + 1) << "/" << times << endl;
    }
    for (int i = 0; i < times; ++i) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        benchResults.sampleKaratsubaAnswer = karatsubaMultiply(x, y);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        duration<double, std::milli> d = t2 - t1;
        benchResults.karatsubaResult += d.count();
        cout << "Made Karatsuba " << d.count() << "ms, " << (i + 1) << "/" << times << endl;
    }
    benchResults.columnResult /= times;
    benchResults.karatsubaResult /= times;
    return benchResults;
}

int main() {
    ifstream input("../input.txt");
    string n1, n2, n3;
    getline(input, n1);
    getline(input, n2);
    getline(input, n3);
    Number x(n1.c_str()), y(n2.c_str()), z(n3.c_str());
    cout << "Got two numbers with " << x.getN() << " and " << y.getN() << " digits " << endl;

    BenchResults benchResults = bench(x, y, timesOfBench);
    if (printAnswer) {
        cout << "The answer is:" << endl << benchResults.sampleColumnAnswer << endl;
    } else {
        cout << "Column got answer" << endl;
    }
    if (benchResults.sampleColumnAnswer == benchResults.sampleKaratsubaAnswer) {
        cout << "Karatsuba agreed" << endl;
    } else if (printAnswer) {
        cout << "Karatsuba think, that the answer is:" << endl << benchResults.sampleKaratsubaAnswer << endl;
    } else {
        cout << "Karatsuba got another answer!" << endl;
    }
    if (benchResults.sampleColumnAnswer != z) {
        cout << "Assertion failed for the column" << endl;
    }
    if (benchResults.sampleKaratsubaAnswer != z) {
        cout << "Assertion failed for the Karatsuba" << endl;
    }
    if (benchResults.sampleColumnAnswer == z && benchResults.sampleKaratsubaAnswer == z) {
        cout << "Assertion succeed" << endl;
    }
    cout << "Performance:" << endl;
    cout << "Column multiplication took\t\t" << benchResults.columnResult << "ms (avg)" << std::endl;
    cout << "Karatsuba multiplication took\t\t" << benchResults.karatsubaResult << "ms (avg)" << std::endl;
}

