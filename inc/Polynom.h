#ifndef POLYNOM_H
# define POLYNOM_H

# include <iostream>
# include <vector>
# include <algorithm>
# include "Monom.h"

class Monom;

class Polynom
{
	 public:
		Polynom();
		Polynom(std::vector<Monom> vecMonoms);
		Polynom (const Polynom &copy);
		Polynom &operator=(const Polynom&);

		void parsePolynom();
		void addMonom(const Monom& monom);
		void printPolynom() const;
		void sortPolynom();
		std::size_t	 findByOrder(std::size_t target);
		void toNull(const Polynom& toNull);

		std::vector<Monom> getVecMonoms() const;
	 private:
	 	std::vector<Monom> m_vecMonoms;
};

#endif
