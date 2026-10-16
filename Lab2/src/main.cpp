#include <iostream>
#include "calc.h"

int main() {
    int a = 10;
    int b = 4;
    
    std::cout << "add: " << Add(a, b) << "\n";
    std::cout << "sub: " << Sub(a, b) << "\n";
    
    return 0;
}
