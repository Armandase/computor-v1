#ifndef POLYNOM_H
# define POLYNOM_H

# include <iostream>
# include <vector>
# include <algorithm>
# include <cmath>
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
		int	 findByOrder(std::size_t target) const;
		void toNull(const Polynom& toNull);
		void cleanVecMonom();

		double computeDiscriminant() const;
		std::pair<double, double> resolveEquation(double discriminant);
		double computeY(double x);

		std::size_t getMaxOrder() const;
		std::tuple<double, double, double> getCoefficient() const;

		std::vector<Monom> getVecMonoms() const;
	 private:
	 	std::vector<Monom> m_vecMonoms;
};

#endif
