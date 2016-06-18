#include "lib.h"

double SVM::f(struct pt x)
{
    double result = 0;
    for (int i = 0; i < size + 1; i++) {
        result += w[i] * x.val[i];
    }
    return result;
}

void SVM::study(int num)
{
    int count = 0;
    std::random_device rnd;
    while (count < num) {
        int index = rnd() % data.size();

        if (data[index].type * f(data[index]) > 1) {
            for (int i = 0; i < size + 1; i++) {
                w[i] -= K * lambda * w[i];
            }
        } else {
            for (int i = 0; i < size + 1; i++) {
                w[i] -= K * (lambda * w[i] - data[index].type * data[index].val[i]);
            }
        }
        count++;
    }
}

double SVM::output(double value[size])
{
    double result = w[size];
    for (int i = 0; i < size; i++) {
        result += w[i] * value[i];
    }
    
    return result;
}

void SVM::show_param(void)
{
    for (int i = 0; i < size + 1; i++) {
        std::cout << w[i] << std::endl;
    }
}

double SVM::calc_margin(struct pt x)
{
    double value[size];
    for (int i = 0; i < size; i++) {
        value[i] = x.val[i];
    }
    if (f(x) * x.type < 0) return 0.0;

    double k = 0.0;
    while (1) {
        for (int i = 0; i < size; i++) {
            value[i] -= x.type * k * w[i];
        }

        if (output(value) * x.type < 0) {
            double result = 0;
            for (int i = 0; i < size; i++) {
                result += w[i] * w[i];
            }
            result = std::sqrt(result);
            result *= k;
            return result;
        }

        k += 0.001;
    }
    return -1;
}



