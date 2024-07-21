#ifndef POLYNOM_H
# define POLYNOM_H

# include <iostream>
# include <vector>
# include <algorithm>
# include <cmath>
# include "Monom.h"
# include "utils.h"
# define DEFAULT_VARIABLE "X"

class Monom;

class Polynom
{
	 public:
		Polynom();
		Polynom(std::vector<Monom> vecMonoms);
		Polynom (const Polynom &copy);
		Polynom &operator=(const Polynom&);

		void parsePolynom(std::string variable = "");
		void addMonom(const Monom& monom);
		void printPolynom() const;
		void sortPolynom();
		int	 findByOrder(std::size_t target) const;
		void toNull(Polynom& toNull);
		void cleanVecMonom();

		double computeDiscriminant() const;
		std::pair<double, double> resolveEquation(double discriminant);
		double computeY(double x);
		void irreducibleForm();

		std::size_t getMaxOrder() const;
		double getValueByOrder(int order) const;
		std::tuple<double, double, double> getCoefficient() const;

		std::vector<Monom> getVecMonoms() const;
	 private:
	 	std::vector<Monom> m_vecMonoms;
};

#endif
