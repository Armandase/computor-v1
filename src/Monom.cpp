#include "../inc/Monom.h"

Monom::Monom(){
	m_order = 0;
    m_value = 0;
	m_variable = std::string();
}

Monom::Monom(const std::string& input, char sign){
	m_order = 0;
    m_value = 0;
	m_variable = std::string();
	parseMonom(input, sign);
}

Monom::Monom(std::string& variable, std::size_t order, double value){
	m_order = order;
    m_value = value;
	m_variable = variable;
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

Monom Monom::operator+(const Monom& add){
	if (add.getOrder() != this->m_order)
	{
		std::cerr << __FUNCTION__ << ": " << " error monom addition between different order" << std::endl;
		exit(1);
	}
	if (add.getVariable() != this->m_variable)
	{
		std::cerr << __FUNCTION__ << ": " << " error monom addition between different variable" << std::endl;
		exit(1);
	}
	return (Monom(m_variable, m_order, m_value + add.getValue()));
}

Monom Monom::operator-(const Monom& sub){
	if (sub.getOrder() != this->m_order)
	{
		std::cerr << __FUNCTION__ << ": " << " error monom substraction between different order" << std::endl;
		exit(1);
	}
	if (sub.getVariable() != this->m_variable)
	{
		std::cerr << __FUNCTION__ << ": " << " error monom substraction between different variable" << std::endl;
		exit(1);
	}
	return (Monom(m_variable, m_order, m_value - sub.getValue()));
}

void Monom::operator+=(const Monom& add){
	if (add.getOrder() != this->m_order)
	{
		std::cerr << __FUNCTION__ << ": " << " error monom assignement addition between different order" << std::endl;
		exit(1);
	}
	if (add.getVariable() != this->m_variable)
	{
		std::cerr << __FUNCTION__ << ": " << " error monom assignement addition between different variable" << std::endl;
		exit(1);
	}
	m_value += add.getValue();
}

void Monom::operator-=(const Monom& sub){
	if (sub.getOrder() != this->m_order)
	{
		std::cerr << __FUNCTION__ << ": " << " error monom  assignement substraction between different order" << std::endl;
		exit(1);
	}
	if (sub.getVariable() != this->m_variable && !sub.getVariable().size() && !m_variable.size())
	{
		std::cerr << __FUNCTION__ << ": " << " error monom assignement substraction between different variable" << std::endl;
		exit(1);
	}
	m_value -= sub.getValue();
}


void Monom::parseMonom(const std::string& input, char sign)
{
	// bool inputDouble = false;
	bool defaultExp = false;
	bool defaultVariable = false;
	bool defaultValue = false;
	char varName = findVariableName(input);

	// if the variable name is undefine, it's set to the default one ('x')
	if (varName == 0)
	{
		varName = m_variable[0];
		defaultVariable = true;
	}

	// find the index of the variable, the value & the expenontial
	int varIndex = findUniqueOf(input, varName);
	int valueIndex = findUniqueOf(input, '*');
	int expIndex = findUniqueOf(input, '^');

	if (varIndex == MULTIPLE_DEFINITION )
	{
		std::cerr << __FUNCTION__ << ": " << " variable name can be just a single char.\n";
		std::cout << "error comes from this monom" << input  << std::endl;
		exit (1);
	}
	if (valueIndex == MULTIPLE_DEFINITION )
	{
		std::cerr << __FUNCTION__ << ": " << " too many '*' in this monom: " << input << std::endl;
		exit(1);
	}
	if (expIndex == MULTIPLE_DEFINITION)
	{
		std::cerr << __FUNCTION__ << ": " << " too many '^' in this monom: " << input << std::endl;;
		exit(1);
	}
	if (valueIndex != NOT_FOUND && varIndex == NOT_FOUND && expIndex == NOT_FOUND)
	{
		std::cerr << __FUNCTION__ << ": " << " nothing comes with '*' in this monom: " << input << std::endl;
		exit(1);
	}

	// if the exponential isn't set, set to 0 as default
	if(expIndex == NOT_FOUND){
		m_order = 0;
		defaultExp = true;
	}
	// if the value isn't set, set to 1 as default
	if (valueIndex == NOT_FOUND)
	{
		m_value = 1;
		defaultValue = true;
	}
    (void)defaultValue;	
	if (!defaultVariable)
		m_variable = std::string(1, varName);
	// check if the '^' is before the 'x' 
	// check also if the number is after the '^' 
	if (valueIndex != NOT_FOUND && expIndex != NOT_FOUND
		&& (expIndex <= varIndex || valueIndex > expIndex))
	{
		std::cerr << __FUNCTION__ << ": " << "wrong placement of an exponential." << std::endl;
		exit(1);
	}

	// if exponential & value aren't set and the input doesn't contains variable name 
	if (expIndex == NOT_FOUND && valueIndex == NOT_FOUND && defaultVariable)
		m_value = convertStringToDouble(input);
	// if exponential & value aren't set and the input contains a variable.
	// it remove the variable and process it to convert the string to a double 
	else if (expIndex == NOT_FOUND && valueIndex == NOT_FOUND && input.size() > 1)
	{
		auto withoutVariable = input;
		withoutVariable.erase(varIndex, varIndex + 1);
		m_value = convertStringToDouble(withoutVariable);
	}
	else {
		if ( valueIndex != NOT_FOUND )
		{
			std::string value = input.substr(0, valueIndex);
			if (valueIndex != NOT_FOUND && value.size() == 0)
			{
				std::cerr << __FUNCTION__ << ": " << "value is empty in this monom: " << input << std::endl;
				exit(1);
			}
			if (!m_value)
				m_value = convertStringToDouble(value);
		}else if (valueIndex == NOT_FOUND && expIndex != NOT_FOUND){
			std::string value;
			if (!defaultVariable)
			{
				value = input.substr(expIndex + 1, input.size() - 1);
			}
			else
			{
				value = input.substr(0, expIndex);
				auto idx = value.find_first_of(m_variable);
				value.erase(value.begin() + idx, value.begin() + idx + 1);
			}
			
			m_value = convertStringToDouble(value);
		}
		if (expIndex != NOT_FOUND)
		{
			std::string order = input.substr(expIndex + 1);
			if (expIndex != NOT_FOUND && order.size() == 0)
			{
				std::cerr << __FUNCTION__ << ": " << "exponential is empty in this monom: " << input << std::endl;
				exit(1);
			}
			if (!m_order && !defaultExp){
				m_order = convertStringToInt(order);
			}
		}
	}

	if (sign == '-')
		m_value *= -1;
}

std::string Monom::monomAsString() const
{
	return std::string(std::to_string(m_value)
	+ " * " + m_variable
	+ "^" + std::to_string(m_order));
}

std::string	Monom::getVariable() const
{ return (m_variable); }

std::size_t	Monom::getOrder() const
{ return (m_order); }

double		Monom::getValue() const
{ return (m_value); }

void	Monom::setVariable(std::string& newVar){
	m_variable = newVar;
}

void	Monom::setValue(double newValue){
	m_value = newValue;
	
}



