#include "../inc/Polynom.h"

Polynom::Polynom(){
	m_vecMonoms = {};
}

Polynom::Polynom(std::vector<Monom> vecMonoms)
{
	m_vecMonoms = vecMonoms;
}

Polynom::Polynom(const Polynom &copy){
	*this = copy;
}

Polynom & Polynom::operator=(const Polynom &copy){
	if (&copy != this)
	{
		m_vecMonoms = copy.m_vecMonoms;
	}
	return (*this);
}


void Polynom::addMonom(const Monom& monom){
	m_vecMonoms.push_back(monom);
}

void Polynom::printPolynom() const
{
	int size = m_vecMonoms.size();
	for (int i = 0; i < size; i++)
	{
		std::cout <<  m_vecMonoms[i].monomAsString();
		if (i + 1 != size)
			std::cout << " + ";
	}	
	std::cout << std::endl;
}


void Polynom::sortPolynom()
{

};