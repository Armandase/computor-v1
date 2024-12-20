#ifndef MONOM_H
# define MONOM_H

# include <iostream>
# include "parsing_utils.h"

class Monom
{
	 public:
		Monom();
		Monom(const std::string& input, char sign);
		Monom(std::string& variable, std::size_t order, double value);


		Monom (const Monom &copy);
		Monom &operator=(const Monom&);
		Monom operator+(const Monom&);
		void operator+=(const Monom&);
		Monom operator-(const Monom&);
		void operator-=(const Monom&);
		bool operator==(const Monom&);
		bool operator!=(const Monom&);
		Monom  abs() const;

		std::string	getVariable() const;
		std::size_t	getOrder() const;
		double		getValue() const;
		void	setValue(double newValue);
		void	setVariable(std::string& newVar);


		void parseMonom(const std::string& input, char sign);
		void extractOrder(const std::string& input);
		void extractValue(const std::string& input);
		std::string monomAsString() const;
	 private:
	 	std::string m_variable;
	 	std::size_t	m_order;
		double 		m_value;
};

#endif
