#pragma once
#include <iostream>
#include <ctime>

class SVM {
public:
    SVM() {
    }

    std::vector<struct pt> data;
    double w[size];
    double b;

    void study(void);
    int output(double value[size]);
};
