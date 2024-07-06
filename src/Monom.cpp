#include "../inc/Monom.h"

Monom::Monom(){
	m_order = 0;
    m_value = 0;
	m_variable = "x";
}

Monom::Monom(const std::string& input, char sign){
	m_order = 0;
    m_value = 0;
	m_variable = "x";
	parseMonom(input, sign);
}

Monom::Monom(const Monom &copy){
	*this = copy;
}

Monom & Monom::operator=(const Monom &copy){
	if (&copy != this)
	{
		m_order = copy.m_order;
		m_value = copy.m_value;
		m_variable = copy.m_variable;
	}
	return (*this);
}

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
	if (varName == 0)
	{
		std::cerr << __FUNCTION__ << ": " << "Variable name not found." << std::endl;
		exit(1);
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
	int result = 0;

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

void Monom::parseMonom(const std::string& input, char sign)
{
	std::cout << "input: " << input << std::endl;
	char varName = findVariableName(input);

	int varIndex = findUniqueOf(input, varName);
	int valueIndex = findUniqueOf(input, '*');
	int expIndex = findUniqueOf(input, '^');

	if(expIndex == -1)
		m_order = 1;
	if (valueIndex == -1)
		m_value = 1;
	if (expIndex <= varIndex)
	{
		std::cerr << __FUNCTION__ << ": " << "wrong placement of an exponential." << std::endl;
		exit(1);
	}
	m_variable = std::string(1, varName);

	std::string value;
	std::string order;

	if (valueIndex < expIndex)
	{
		value = input.substr(0, valueIndex);
		order = input.substr(expIndex + 1);
	} else {
		value = input.substr(valueIndex + 1);
		order = input.substr(expIndex + 1, valueIndex - expIndex - 1);
	}
	if (!m_value)
		m_value = convertStringToDouble(value);
	if (!m_order)
		m_order = convertStringToInt(order);
	if (sign == '-')
		m_value *= -1;
}

std::string Monom::monomAsString() const
{
	return std::string(std::to_string(m_value)
	+ " * " + m_variable
	+ "^" + std::to_string(m_order));
}