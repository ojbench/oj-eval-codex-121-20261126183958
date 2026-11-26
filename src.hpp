#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
    divided_by_zero() = default;
    ~divided_by_zero() = default;
    const char *what() const noexcept override {
        return "complex divided by zero!";
    }
};

inline int sign(double x) {
    const double eps = 1e-6;
    return (x > eps) - (x < -eps);
}

class complex {
private:
    double a, b;

public:
    complex() : a(0), b(0) {}
    complex(double real) : a(real), b(0) {}
    complex(double real, double imag) : a(real), b(imag) {}
    complex(const complex &) = default;
    complex &operator=(const complex &) = default;

    double &real() { return a; }
    double &imag() { return b; }

    complex operator-() const { return complex(-a, -b); }
    complex operator~() const { return complex(a, -b); }

    complex operator+(const complex &rhs) const {
        return complex(a + rhs.a, b + rhs.b);
    }
    complex operator-(const complex &rhs) const {
        return complex(a - rhs.a, b - rhs.b);
    }
    complex operator*(const complex &rhs) const {
        return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
    }
    complex operator/(const complex &rhs) const {
        if (!rhs) throw divided_by_zero();
        const double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
        return complex((a * rhs.a + b * rhs.b) / denominator,
                       (b * rhs.a - a * rhs.b) / denominator);
    }

    complex &operator+=(const complex &rhs) { return *this = *this + rhs; }
    complex &operator-=(const complex &rhs) { return *this = *this - rhs; }
    complex &operator*=(const complex &rhs) { return *this = *this * rhs; }
    complex &operator/=(const complex &rhs) { return *this = *this / rhs; }

    bool operator==(const complex &rhs) const {
        return std::fabs(a - rhs.a) < 1e-6 && std::fabs(b - rhs.b) < 1e-6;
    }
    explicit operator bool() const { return !(*this == complex()); }

    friend std::ostream &operator<<(std::ostream &os, const complex &x) {
        const auto flags = os.flags();
        const auto precision = os.precision();
        os << std::fixed << std::setprecision(6) << std::noshowpos;
        if (sign(x.a) < 0) os << '-';
        os << std::fabs(x.a) << (sign(x.b) < 0 ? '-' : '+')
           << std::fabs(x.b) << 'i';
        os.flags(flags);
        os.precision(precision);
        return os;
    }
};

} // namespace sjtu

#endif
