#include "../inc/parsing.h"
#include "../inc/matplotlibcpp.h"
#include "../inc/utils.h" 
#include <iostream>

namespace plt = matplotlibcpp;

void plotGraph(Polynom& equation)
{
    std::vector<double> x;
    std::vector<double> y;

    for (double i = -10; i < 10; i += 0.1)
    {
        x.push_back(i);
        y.push_back(equation.computeY(i));
    }

    plt::plot(x, y);
    plt::title("Polynom");
    plt::xlabel("x");
    plt::ylabel("y");
    plt::show();
    Py_Finalize();
}

static int computor_v1(std::string& input)
{
    Polynom equation = handleInput(input);
    if (equation.getVecMonoms().empty())
    {
        std::cerr << "This is a trivial equation with an infinit number of solution." << std::endl;
        return 1;
    }
    auto maxOrder = equation.getMaxOrder();
    std::cout << "Reduced form: ";
    equation.printPolynom();
    std::cout << " = 0\n";
    equation.irreducibleForm();
    std::cout <<  "Polynomial degree: " << maxOrder << std::endl;
    if (maxOrder > 2)
    {
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
        return (0);
    }

    if (maxOrder == 1){
        double a = equation.getValueByOrder(1);
        double b = equation.getValueByOrder(0);

        std::cout << "The solution is:" << std::endl;
        std::cout << -b / a << std::endl;

    } else if (maxOrder == 2){
        double discriminant = equation.computeDiscriminant();
        std::cout << "The disciminant is " <<  discriminant << std::endl;
        if (discriminant < 0)
        {
            std::cout << "Discriminant is strictly negative, the two complex solutions are" << std::endl;
            auto a = equation.getValueByOrder(2);
            auto b = equation.getValueByOrder(1);
            std::cout << "(" << -b << " - i * √" << -discriminant << ") / " << 2 * a << std::endl;
            std::cout << "(" << -b << " + i * √" << -discriminant << ") / " << 2 * a << std::endl;
        } else if (discriminant == 0){
            std::cout << "Discriminant is null, the solution is:" << std::endl;
            std::cout << equation.resolveEquation(discriminant).first << std::endl;
        } else {
            std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
            auto result = equation.resolveEquation(discriminant);
            std::cout << result.first << std::endl;
            std::cout << result.second << std::endl;
        }
    }
    if (ACTIVATE_PLOT == 1)
        plotGraph(equation);
    else
        std::cout << "Plot desactivated." << std::endl;
    return 0;
}

int main(int ac, char** av)
{
    if (ac != 2 || !av[1]){
        std::cerr << "Wrong number of agruments." << std::endl;
        return 1;
    }

    std::string input(av[1]);

    try
    {
        int ret = computor_v1(input);
        return (ret);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}