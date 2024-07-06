#ifndef MONOM_H
# define MONOM_H

# include <iostream>

class Monom
{
	 public:
		Monom();
		Monom(const std::string& input, char sign);

		Monom (const Monom &copy);
		Monom &operator=(const Monom&);
		
		void parseMonom(const std::string& input, char sign);
		std::string monomAsString() const;


	 private:
	 	std::string m_variable;
	 	std::size_t	m_order;
		double 		m_value;
};

#endif
