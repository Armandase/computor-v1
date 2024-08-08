#include "../inc/parsing_utils.h"

int findUniqueOf(const std::string& str, char target)
{
	auto index = str.find_first_of(target);
	
	if (str.find_last_of(target) != index)
		return (MULTIPLE_DEFINITION);
	if (index == std::string::npos)
		return (NOT_FOUND); 

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
			throw std::runtime_error(std::string(__FUNCTION__) + ": " + "Multiple variable declaration in a monom.");
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
			throw std::runtime_error(std::string(__FUNCTION__) + ": " + "another char in the exponential section.");
		}
	}

	try {
		result = std::stoi(str);
	} catch (std::invalid_argument &e) {
		throw std::runtime_error(std::string(__FUNCTION__) + ": " + "stoi invalid argument");
	} catch (std::exception &e) {
		throw std::runtime_error(std::string(__FUNCTION__) + ": " + "stoi exception");
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
			throw std::runtime_error(std::string(__FUNCTION__) + ": " + "another char in the exponential section.");
		}
		if (str[i] == '.')
		{
			if (dot)
			{
				std::runtime_error(std::string(__FUNCTION__) + ": " + "multiple dots in the value section.");
			}
			dot = true;
		}
	}

	try {
		result = std::stod(str);
	} catch (std::invalid_argument &e) {
		throw std::runtime_error(std::string(__FUNCTION__) + ": " + "stod invalid argument");
	} catch (std::exception &e) {
		throw std::runtime_error(std::string(__FUNCTION__) + ": " + "stod exception");
	}
	return (result);
}
