#ifndef PARSING_H
# define PARSING_H

# include <vector>
# include <sstream>
# include <iostream>
# include <string>
# include <algorithm>
# include "../inc/Monom.h"
# include "../inc/Polynom.h"

# define POSITIVE 0
# define NEGATIVE 1

Polynom    handleInput(std::string& input);
std::vector<std::string> splitWithDelim(std::string in, std::string delim);
int     foundOccurenceOf(const std::string& input, char target);
std::vector<std::pair<std::string, char> > getMonoms(std::string input);
int     findUniqueOf(const std::string& str, char target);
char    findVariableName(const std::string& str);
int     convertStringToInt(const std::string& str);
double  convertStringToDouble(const std::string& str);  
// Polynom getMonomFromString(const std::string& str);

#endif