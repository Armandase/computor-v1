#include "../inc/parsing.h"

int findUniqueOf(const std::string& str, char target)
{
	auto index = str.find_first_of(target);
	
	if (str.find_last_of(target) != index || index == std::string::npos)
	{
		return (-1); 
	}

	return (index);
}

char	findVariableName(const std::string& str)
{
	int size = str.size();
	char varName = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (std::isalpha(str[i]) && varName == 0)
			varName = str[i];
		else if (std::isalpha(str[i]))
		{
			std::cerr << __FUNCTION__ << ": " << "Multiple variable declaration in a monom." << std::endl;
			exit(1);
		}
	}
	return (varName);
}

int convertStringToInt(const std::string& str)
{
	int result = 0;

	for (std::size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cerr << __FUNCTION__ << ": " << "another char in the exponential section." << std::endl;
			exit(1);
		}
	}

	try {
		result = std::stoi(str);
	} catch (std::invalid_argument &e) {
		std::cerr << __FUNCTION__ << ": " << "stoi invalid argument" << std::endl;
		exit(1);
	} catch (std::exception &e) {
		std::cerr << __FUNCTION__ << ": " << " exception throw from " << e.what() << std::endl;
		exit(1);
	}
	return (result);
}

double convertStringToDouble(const std::string& str)
{
	double result = 0;

	bool dot = false;
	for (std::size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]) && str[i] != '.')
		{
			std::cerr << __FUNCTION__ << ": " << "another char in the exponential section." << std::endl;
			exit(1);
		}
		if (str[i] == '.')
		{
			if (dot)
			{
				std::cerr << __FUNCTION__ << ": " << "multiple dots in the value section." << std::endl;
				exit(1);
			}
			dot = true;
		}
	}

	try {
		result = std::stod(str);
	} catch (std::invalid_argument &e) {
		std::cerr << __FUNCTION__ << ": " << "stod invalid argument" << std::endl;
		exit(1);
	} catch (std::exception &e) {
		std::cerr << __FUNCTION__ << ": " << " exception throw from " << e.what() << std::endl;
		exit(1);
	}
	return (result);
}
