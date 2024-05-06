// Variadic arrays
// Copyright Laurence Emms 2024


#include <iostream>
#include <sstream>
#include <string>

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

    var::Array<double, 3> three_1(1.0);

    std::cout << "Three_1[0]: " << var::get<0>(three_1) << std::endl;
    std::cout << "Three_1[1]: " << var::get<1>(three_1) << std::endl;
    std::cout << "Three_1[2]: " << var::get<2>(three_1) << std::endl;

    // The following is a compile error
    // std::cout << "Three_1[3]: " << var::get<3>(three_1) << std::endl;

    var::Array<double, 3> three_copy(three);

    std::cout << "Three_copy[0]: " << var::get<0>(three_copy) << std::endl;
    std::cout << "Three_copy[1]: " << var::get<1>(three_copy) << std::endl;
    std::cout << "Three_copy[2]: " << var::get<2>(three_copy) << std::endl;

    // The following is a compile error
    // std::cout << "Three_copy[3]: " << var::get<3>(three_copy) << std::endl;

    var::Array<double, 3> three_assignment = three_copy;

    std::cout << "Three_assignment[0]: " << var::get<0>(three_assignment) << std::endl;
    std::cout << "Three_assignment[1]: " << var::get<1>(three_assignment) << std::endl;
    std::cout << "Three_assignment[2]: " << var::get<2>(three_assignment) << std::endl;

    // The following is a compile error
    // std::cout << "Three_assignment[3]: " << var::get<3>(three_assignment) << std::endl;

    var::Array<double, 3> three_arithmetic;

    std::cout << "Three_arithmetic[0]: " << var::get<0>(three_arithmetic) << std::endl;
    std::cout << "Three_arithmetic[1]: " << var::get<1>(three_arithmetic) << std::endl;
    std::cout << "Three_arithmetic[2]: " << var::get<2>(three_arithmetic) << std::endl;

    // The following is a compile error
    // std::cout << "Three_arithmetic[3]: " << var::get<3>(three_arithmetic) << std::endl;

    var::Array<std::string, 3> three_non_arithmetic{"Hello", ",", " world!"};

    std::cout << "Three_non_arithmetic[0]: " << var::get<0>(three_non_arithmetic) << std::endl;
    std::cout << "Three_non_arithmetic[1]: " << var::get<1>(three_non_arithmetic) << std::endl;
    std::cout << "Three_non_arithmetic[2]: " << var::get<2>(three_non_arithmetic) << std::endl;

    // The following is a compile error because std::string is not an arithmetic type
    //var::Array<std::string, 3> three_non_arithmetic;

    var::Array<double, 3> three_sum = var::map(three, three_1, 0.0, [](double lhs, double rhs) -> double { return lhs + rhs; });

    std::cout << "Three_sum[0]: " << var::get<0>(three_sum) << std::endl;
    std::cout << "Three_sum[1]: " << var::get<1>(three_sum) << std::endl;
    std::cout << "Three_sum[2]: " << var::get<2>(three_sum) << std::endl;

    // The following is a compile error
    // std::cout << "Three_sum[3]: " << var::get<3>(three_sum) << std::endl;

    double three_sum_foldl = var::foldl(three_sum, 0.0, [](double lhs, double rhs) -> double { return lhs + rhs; });

    std::cout << "Three_sum foldl: " << three_sum_foldl << std::endl;

    double three_sum_foldr = var::foldr(three_sum, 0.0, [](double lhs, double rhs) -> double { return lhs + rhs; });

    std::cout << "Three_sum foldr: " << three_sum_foldr << std::endl;

    std::string three_concat = var::foldl(three_non_arithmetic, std::string(), [](const std::string& lhs, const std::string& rhs) -> std::string {
            std::stringstream ss;
            ss << lhs << rhs;
            return ss.str();
            });

    std::cout << "Three concat: " << three_concat << std::endl;

    return 0;
}
