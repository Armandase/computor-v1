#include "../inc/Polynom.h"
#include <unordered_map>

Polynom::Polynom() {
  m_vecMonoms = {};
  m_defaultVariable = true;
}

Polynom::Polynom(std::vector<Monom> vecMonoms) {
  m_vecMonoms = vecMonoms;
  m_defaultVariable = true;
  parsePolynom();
  sortPolynom();
  removeEqualMonoms();
}

Polynom::Polynom(const Polynom &copy) { *this = copy; }

Polynom &Polynom::operator=(const Polynom &copy) {
  if (&copy != this) {
    m_vecMonoms = copy.m_vecMonoms;
  }
  return (*this);
}

void Polynom::parsePolynom(std::string variable) {
  int size = m_vecMonoms.size();
  if (variable.empty()) {
    for (int i = 0; i < size; i++) {
      if (m_vecMonoms[i].getVariable().size() == 1 &&
          m_vecMonoms[i].getVariable()[0] != 0) {
        variable = m_vecMonoms[i].getVariable();
        m_defaultVariable = false;
        break;
      }
    }
  }
  if (variable.empty()) {
    variable = DEFAULT_VARIABLE;
    for (int i = 0; i < size; i++)
      m_vecMonoms[i].setVariable(variable);
  } else {
    m_defaultVariable = false;
    for (int i = 0; i < size; i++) {
      if ((m_vecMonoms[i].getVariable().size() == 1 &&
           m_vecMonoms[i].getVariable()[0] == 0) ||
          m_vecMonoms[i].getVariable().empty())
        m_vecMonoms[i].setVariable(variable);

      if (m_vecMonoms[i].getVariable().size() == 1 &&
          m_vecMonoms[i].getVariable()[0] != 0 &&
          m_vecMonoms[i].getVariable() != variable) {
        throw std::runtime_error(std::string(__FUNCTION__) + ": " +
                                 "error variable mismatch");
      }
    }
  }
}
void Polynom::removeEqualMonoms() {
  std::unordered_map<int, Monom> elementSum(m_vecMonoms.size());
  for (Monom &num : m_vecMonoms) {
    if (elementSum.find(num.getOrder()) == elementSum.end()) {
      elementSum[num.getOrder()] = num;
      continue;
    }
    elementSum[num.getOrder()] += num;
  }
  m_vecMonoms.clear();
  for (const auto &[key, sum] : elementSum) {
    m_vecMonoms.push_back(sum);
  }
}

void Polynom::addMonom(const Monom &monom) { m_vecMonoms.push_back(monom); }

void Polynom::printPolynom() const {
  int size = m_vecMonoms.size();
  for (int i = 0; i < size; i++) {
    std::cout << m_vecMonoms[i].monomAsString();
    if (i + 1 != size)
      std::cout << " + ";
  }
}

void Polynom::sortPolynom() {
  std::sort(m_vecMonoms.begin(), m_vecMonoms.end(),
            [](const Monom &p1, const Monom &p2) {
              return (p1.getOrder() > p2.getOrder());
            });
};

int Polynom::findByOrder(std::size_t target) const {
  int size = m_vecMonoms.size();
  for (int i = 0; i < size; i++) {
    if (m_vecMonoms[i].getOrder() == target)
      return (i);
  }
  return -1;
}

void Polynom::toNull(Polynom &toNull) {
  if (toNull.getMaxOrder() > this->getMaxOrder()) {
    auto tmp = *this;
    *this = toNull;
    toNull = tmp;
  }
  if (m_defaultVariable == true)
    toNull.parsePolynom();
  else
    toNull.parsePolynom(m_vecMonoms.begin()->getVariable());
  if (toNull.getMaxOrder() == 0 && this->getMaxOrder() == 0)
    return;
  if (m_defaultVariable == true)
    setVariables(toNull.getVecMonoms()[0].getVariable());
  int size = toNull.getVecMonoms().size();
  int idx = 0;
  for (int i = 0; i < size; i++) {
    idx = findByOrder(toNull.getVecMonoms()[i].getOrder());
    if (idx == -1) {
      std::string name = toNull.getVecMonoms()[i].getVariable();
      m_vecMonoms.push_back(Monom(name, toNull.getVecMonoms()[i].getOrder(),
                                  -toNull.getVecMonoms()[i].getValue()));
      continue;
    }

    if (toNull.getVecMonoms()[i].getValue() < 0)
      this->m_vecMonoms[idx] += toNull.getVecMonoms()[i].abs();
    else
      this->m_vecMonoms[idx] -= toNull.getVecMonoms()[i].abs();
  }
  // cleanVecMonom();
}

void Polynom::cleanVecMonom() {
  std::vector<size_t> deleteIndexes = {};
  for (size_t i = 0; i < this->m_vecMonoms.size(); i++) {
    if (m_vecMonoms[i].getValue() == 0)
      deleteIndexes.push_back(i);
  }

  for (int i = deleteIndexes.size() - 1; i >= 0; i--) {
    auto iterator = m_vecMonoms.begin() + deleteIndexes[i];
    m_vecMonoms.erase(iterator);
  }
}

void Polynom::setVariables(std::string name) {
  for (auto &monom : m_vecMonoms)
    monom.setVariable(name);
}

std::vector<Monom> Polynom::getVecMonoms() const { return (m_vecMonoms); }

std::size_t Polynom::getMaxOrder() const {
  std::size_t max = 0;

  for (auto &monom : m_vecMonoms) {
    if (monom.getOrder() > max && monom.getValue()) {
      max = monom.getOrder();
    }
  }
  return max;
}

std::tuple<double, double, double> Polynom::getCoefficient() const {
  if (getMaxOrder() != 2) {
    throw std::runtime_error(
        std::string(__FUNCTION__) + ": " +
        "Can't compute the discrimiant on a non second degree polynom.");
  }

  double a = getValueByOrder(2);
  double b = getValueByOrder(1);
  double c = getValueByOrder(0);

  return {a, b, c};
}

double Polynom::getValueByOrder(int order) const {
  int idx = findByOrder(order);
  double result = 0;
  if (idx == -1)
    result = 0;
  else
    result = m_vecMonoms[idx].getValue();
  return result;
}

double Polynom::computeDiscriminant() const {
  auto coefficients = getCoefficient();
  double a = std::get<0>(coefficients);
  double b = std::get<1>(coefficients);
  double c = std::get<2>(coefficients);

  return (b * b - 4 * (a * c));
}

std::pair<double, double> Polynom::resolveEquation(double discriminant) {
  if (discriminant < 0)
    return {0., 0.};

  auto coefficients = getCoefficient();
  double a = std::get<0>(coefficients);
  double b = std::get<1>(coefficients);
  if (discriminant == 0) {
    return {(-b / (2 * a)), 0.};
  } else {
    auto addResult = (-b + std::sqrt(discriminant)) / (2 * a);
    auto subResult = (-b - std::sqrt(discriminant)) / (2 * a);
    return {addResult, subResult};
  }
  return {0., 0.};
}

double Polynom::computeY(double x) {
  size_t size = m_vecMonoms.size();
  double sum = 0.;

  for (size_t i = 0; i < size; i++) {
    sum += m_vecMonoms[i].getValue() * (std::pow(x, m_vecMonoms[i].getOrder()));
  }
  return sum;
}

void Polynom::irreducibleForm() {
  std::vector<int> coefficients(this->m_vecMonoms.size());

  for (auto &monom : this->m_vecMonoms)
    coefficients.push_back(monom.getValue());

  int gcd = gcd_of_n(coefficients);

  if (gcd <= 1) {
    std::cout << "This polynom can't be simplified." << std::endl;
    return;
  }

  for (auto &monom : this->m_vecMonoms)
    monom.setValue(monom.getValue() / gcd);
  std::cout << std::string(__FUNCTION__) << ": "
            << "each coefficient has been divided by " << gcd << std::endl;
  std::cout << "The reduced polynom is: ";
  this->printPolynom();
  std::cout << std::endl;
}
