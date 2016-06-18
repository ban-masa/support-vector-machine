#pragma once


#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>

constexpr int size = 2;
constexpr double K = 0.1;
constexpr double lambda = 0.0001;
constexpr int MAX = 1000;

#include "SVM.h"
struct pt {
    double val[size + 1];
    double type;
};

