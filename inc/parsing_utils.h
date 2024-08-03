#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include <iostream>

# define NOT_FOUND -1
# define MULTIPLE_DEFINITION -2 

int     findUniqueOf(const std::string& str, char target);
char    findVariableName(const std::string& str);
int     convertStringToInt(const std::string& str);
double  convertStringToDouble(const std::string& str);  
// Polynom getMonomFromString(const std::string& str);

#endif