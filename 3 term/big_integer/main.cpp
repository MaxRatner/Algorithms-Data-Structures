#include <iostream>
#include "biginteger.h"

int main() {
    BigInteger b1 = -0;
    BigInteger b2 = 0;
    long long a1 = -1, a2 = 1;
    //std::cout << b1 * b1 / b1 << ' ' << a1 % 7 << "\n";
    std::cout << (b1 < b2) << "\n";//<< ' ' << a1 + a2 << "\n";
    std::cout << (b1 > b2) << "\n";// << ' ' << a1 - a2 << "\n";
    std::cout << (b1 == b2) << "\n";//<< ' ' << a1 * a2 << "\n";
    std::cout << b1 / b2 << "\n";// << ' ' << a1 / a2 << "\n";
    std::cout << b1 % 7 << "\n"; //<< ' ' << a1 % 7 << "\n";
    if (!b1) {
        std::cout << "yes";
    }
}//123456789 - 123450000