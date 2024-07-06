#ifndef POLYNOM_H
# define POLYNOM_H

# include <iostream>
# include <vector>
# include "Monom.h"

class Polynom
{
	 public:
		Polynom();
		Polynom(std::vector<Monom> vecMonoms);
		Polynom (const Polynom &copy);
		Polynom &operator=(const Polynom&);

		void addMonom(const Monom& monom);
		void printPolynom() const;
		void sortPolynom();
	 private:
	 	std::vector<Monom> m_vecMonoms;
};

#endif
