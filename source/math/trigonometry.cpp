#include "trigonometry.h"
#include <cmath>

namespace earthgen {

double triangle_area (double a, double b, double c) {
    double semi_perimeter = (a + b + c) * 0.5;
    auto f = [=](double s) {return semi_perimeter - s;};
    return std::sqrt(semi_perimeter * f(a) * f(b) * f(c));
}

}
