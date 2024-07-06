#ifndef PARSING_H
# define PARSING_H

# include <vector>
# include <sstream>
# include <iostream>

# define POSITIVE 0
# define NEGATIVE 1

void handleInput(std::string& input);
std::vector<std::string> splitWithDelim(std::string in, std::string delim);
int foundOccurenceOf(const std::string& input, char target);
std::vector<std::pair<std::string, char> > getMonoms(std::string input);

#endif