#include "../inc/Polynom.h"

Polynom::Polynom(){
	m_vecMonoms = {};
}

Polynom::Polynom(std::vector<Monom> vecMonoms)
{
	m_vecMonoms = vecMonoms;
	parsePolynom();
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

void Polynom::parsePolynom()
{
	std::string variable;
	int size = m_vecMonoms.size();

	for (int i = 0; i < size; i++){
		if (i == 0)
			variable = m_vecMonoms[i].getVariable();
		if (variable != m_vecMonoms[i].getVariable())
		{
			std::cerr << __FUNCTION__ << ": " << "Different variable inside a polynom" << std::endl;
			exit(1);
		}
	}
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

bool compareByOrder(const Monom& p1, const Monom& p2) 
{ 
    return p1.getOrder() < p2.getOrder(); 
} 

void Polynom::sortPolynom()
{
	std::sort(m_vecMonoms.begin(), m_vecMonoms.end(), compareByOrder); 
};

std::size_t Polynom::findByOrder(std::size_t target)
{
	for (std::size_t i = 0; i < m_vecMonoms.size(); i++)
	{
		if (m_vecMonoms[i].getOrder() == target)
			return (i);
	}
	return -1;
}

void Polynom::toNull(const Polynom& toNull)
{
	int size = toNull.getVecMonoms().size();
	int idx = 0;
	for (int i = 0; i < size; i++)
	{
		idx = findByOrder(toNull.getVecMonoms()[i].getOrder());
		if (idx == -1)
		{
			std::cerr << __FUNCTION__ << ": " << "miss matching monom between right and left parts" << std::endl;
			exit(1);
		}
		
		if (toNull.getVecMonoms()[i].getValue() < 0)
			this->m_vecMonoms[idx] += toNull.getVecMonoms()[i];			
		else
			this->m_vecMonoms[idx] -= toNull.getVecMonoms()[i];			
	}
}

std::vector<Monom> Polynom::getVecMonoms() const{
	return (m_vecMonoms);
}
