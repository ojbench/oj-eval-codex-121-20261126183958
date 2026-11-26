#include "../src.hpp"
#include <cassert>
#include <complex>
#include <random>
#include <sstream>
#include <string>

int main() {
    using sjtu::complex;
    complex z;
    assert(!z);
    z.real() = 3;
    z.imag() = 4;
    assert(-z == complex(-3, -4));
    assert(~z == complex(3, -4));
    z *= z;
    assert(z == complex(-7, 24));
    z /= z;
    assert(z == complex(1));
    z += z;
    assert(z == complex(2));
    z -= z;
    assert(!z);
    assert(!complex(0.9e-6, -0.9e-6));
    assert(static_cast<bool>(complex(1e-6)));
    assert(!(complex(0) == complex(1e-6)));
    z = 7;
    try {
        z /= complex(0.5e-6, -0.5e-6);
        assert(false);
    } catch (const std::exception &error) {
        assert(std::string(error.what()) == "complex divided by zero!");
        assert(z == complex(7));
    }
    std::ostringstream out;
    out << complex(-2, 0) << ' ' << complex(0, -2) << ' '
        << complex(1, -1e-10) << ' ' << complex(-1e-10, 1);
    assert(out.str() == "-2.000000+0.000000i 0.000000-2.000000i "
                        "1.000000+0.000000i 0.000000+1.000000i");

    std::mt19937 generator(121);
    std::uniform_real_distribution<double> value(-100, 100);
    for (int i = 0; i < 100000; ++i) {
        double a = value(generator), b = value(generator);
        double c = value(generator), d = value(generator);
        complex x(a, b), y(c, d);
        std::complex<double> sx(a, b), sy(c, d);
        auto check = [](complex actual, std::complex<double> expected) {
            assert(std::fabs(actual.real() - expected.real()) < 1e-8);
            assert(std::fabs(actual.imag() - expected.imag()) < 1e-8);
        };
        check(x + y, sx + sy);
        check(x - y, sx - sy);
        check(x * y, sx * sy);
        check(x / y, sx / sy);
    }
}
