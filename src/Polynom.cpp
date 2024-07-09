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
}

bool compareByOrder(const Monom& p1, const Monom& p2) 
{ 
    return p1.getOrder() < p2.getOrder(); 
} 

void Polynom::sortPolynom()
{
	std::sort(m_vecMonoms.begin(), m_vecMonoms.end(), compareByOrder); 
};

int Polynom::findByOrder(std::size_t target) const
{
	int size = m_vecMonoms.size();
	for (int i = 0; i < size; i++)
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
	cleanVecMonom();
}

void Polynom::cleanVecMonom()
{
	std::vector<int> deleteIndexes = {};
	for (size_t i = 0; i < this->m_vecMonoms.size(); i++)
	{
		if (m_vecMonoms[i].getValue() == 0)
			deleteIndexes.push_back(i);
	}

	for (size_t i = deleteIndexes.size(); i > 0; i--)
	{
		auto iterator = m_vecMonoms.begin() + deleteIndexes[i];
		m_vecMonoms.erase(iterator);
	}

}

std::vector<Monom> Polynom::getVecMonoms() const{
	return (m_vecMonoms);
}

std::size_t Polynom::getMaxOrder() const{
	std::size_t max = 0;

	for (auto& monom: m_vecMonoms){
		if (monom.getOrder() > max){
			max = monom.getOrder();
		}
	}
	return max;
}

std::tuple<double, double, double> Polynom::getCoefficient() const {
	if (getMaxOrder() != 2){
		std::cerr << __FUNCTION__ << ": " << "Can't compute the discrimiant on a non second degree polynom." << std::endl;
		exit(1);
	}

	double a = 0, b = 0, c = 0;

	int idx = findByOrder(2);
	if (idx == -1){
		std::cerr << __FUNCTION__ << ": " << "This isn't a second degree polynom" << std::endl;
		exit(1);
	}
	a = m_vecMonoms[idx].getValue();
	
	idx = findByOrder(1);
	if (idx == -1)
		b = 0;
	else
		b = m_vecMonoms[idx].getValue();

	idx = findByOrder(0);
	if (idx == -1)
		c = 0;
	else
		c = m_vecMonoms[idx].getValue();
	return {a, b, c};
}

double Polynom::computeDiscriminant() const
{
	auto coefficients = getCoefficient();
	double a = std::get<0>(coefficients);
	double b = std::get<1>(coefficients);
	double c = std::get<2>(coefficients);

	return (b * b - 4 * (a * c));
}

std::pair<double, double> Polynom::resolveEquation(double discriminant){
	if (discriminant < 0)
		return {0., 0.};
	
	auto coefficients = getCoefficient();
	double a = std::get<0>(coefficients);
	double b = std::get<1>(coefficients);
	if (discriminant == 0){
		return {(-b / (2 * a)), 0.};
	} else {
		auto addResult = (-b + std::sqrt(discriminant))/ (2 * a);
		auto subResult = (-b - std::sqrt(discriminant))/ (2 * a);
		return {addResult, subResult};
	}
	return {0., 0.};
}

double Polynom::computeY(double x){
	size_t size = m_vecMonoms.size();
	double sum = 0.;

	for (size_t i = 0; i < size; i++){
		sum += m_vecMonoms[i].getValue() * (std::pow(x, m_vecMonoms[i].getOrder()));
	}
	return sum;
}