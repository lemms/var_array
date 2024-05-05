// Variadic arrays
// Copyright Laurence Emms 2024


#include <iostream>

#include "var_array.h"


int main(int argc, char** argv) {
    std::cout << "Variadic arrays" << std::endl;

    var::Array<double, 1> one{0.25};

    var::Array<double, 2> two{0.25, 0.5};

    var::Array<double, 3> three{0.25, 0.5, 0.75};

    std::cout << "One[0]: " << var::get<0>(one) << std::endl;

    // The following is a compile error
    // std::cout << "One[1]: " << var::get<1>(one) << std::endl;

    std::cout << "Two[0]: " << var::get<0>(two) << std::endl;
    std::cout << "Two[1]: " << var::get<1>(two) << std::endl;

    // The following is a compile error
    // std::cout << "Two[2]: " << var::get<2>(two) << std::endl;

    std::cout << "Three[0]: " << var::get<0>(three) << std::endl;
    std::cout << "Three[1]: " << var::get<1>(three) << std::endl;
    std::cout << "Three[2]: " << var::get<2>(three) << std::endl;

    // The following is a compile error
    // std::cout << "Three[3]: " << var::get<3>(three) << std::endl;

    return 0;
}
