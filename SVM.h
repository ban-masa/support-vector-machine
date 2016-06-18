#pragma once
#include <iostream>
#include <ctime>

class SVM {
public:
    SVM() {
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());
        std::uniform_real_distribution<> dist1(-1.0, 1.0);

        for (int i = 0; i < size + 1; i++) {
            w[i] = dist1(engine);
        }
    }

    std::vector<struct pt> data;
    double w[size + 1];

    double f(struct pt x);
    double f(double value[size]);

    void study(int num);
    double output(double value[size]);
    void show_param(void);
    double calc_margin(struct pt x);
};
