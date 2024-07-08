#include "../inc/parsing.h"
#include <iostream>

int main(int ac, char** av)
{
    if (ac != 2 || !av[1]){
        std::cerr << "Wrong number of agruments." << std::endl;
        return 1;
    }

    std::string input = av[1];
    Polynom equation = handleInput(input);
    
    auto maxOrder = equation.getMaxOrder();
    std::cout << "Reduced form: ";
    equation.printPolynom();
    std::cout << " = 0\n";
    std::cout <<  "Polynomial degree: " << maxOrder << std::endl;
    if (maxOrder > 2)
    {
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
    }

    double discriminant = equation.computeDiscriminant();
    std::cout << "The disciminant is " <<  discriminant << std::endl;
    if (discriminant < 0)
    {
        std::cout << "Discriminant is strictly negative, there is not solution." << std::endl;
    } else if (discriminant == 0){
        std::cout << "Discriminant is null, the solution is:" << std::endl;
        std::cout << equation.resolveEquation(discriminant).first << std::endl;
    } else {
        std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
        auto result = equation.resolveEquation(discriminant);
        std::cout << result.first << std::endl;
        std::cout << result.second << std::endl;
    }

    
    return 0;
}