#include "../inc/parsing.h"
#include <iostream>

int main(int ac, char** av)
{
    if (ac != 2 || !av[1]){
        std::cerr << "Wrong number of agruments." << std::endl;
        return 1;
    }

    std::string input = av[1];
    handleInput(input);

    return 0;
}