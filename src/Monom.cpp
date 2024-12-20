#include "../inc/Monom.h"

Monom::Monom() {
  m_order = 0;
  m_value = 0;
  m_variable = std::string();
}

Monom::Monom(const std::string &input, char sign) {
  m_order = 0;
  m_value = 0;
  m_variable = std::string();
  parseMonom(input, sign);
}

Monom::Monom(std::string &variable, std::size_t order, double value) {
  m_order = order;
  m_value = value;
  m_variable = variable;
}

Monom::Monom(const Monom &copy) { *this = copy; }

Monom &Monom::operator=(const Monom &copy) {
  if (&copy != this) {
    m_order = copy.m_order;
    m_value = copy.m_value;
    m_variable = copy.m_variable;
  }
  return (*this);
}

Monom Monom::operator+(const Monom &add) {
  if (add.getOrder() != this->m_order) {
    throw std::runtime_error(std::string(__FUNCTION__) + ": " +
                             " error monom addition between different order");
  }
  if (add.getVariable() != this->m_variable) {
    throw std::runtime_error(
        std::string(__FUNCTION__) + ": " +
        " error monom addition between different variable");
  }
  return (Monom(m_variable, m_order, m_value + add.getValue()));
}

Monom Monom::operator-(const Monom &sub) {
  if (sub.getOrder() != this->m_order) {
    throw std::runtime_error(
        std::string(__FUNCTION__) + ": " +
        " error monom substraction between different order");
  }
  if (sub.getVariable() != this->m_variable) {
    throw std::runtime_error(
        std::string(__FUNCTION__) + ": " +
        " error monom substraction between different variable");
  }
  return (Monom(m_variable, m_order, m_value - sub.getValue()));
}

void Monom::operator+=(const Monom &add) {
  if (add.getOrder() != this->m_order) {
    throw std::runtime_error(
        std::string(__FUNCTION__) + ": " +
        " error monom assignement addition between different order");
  }
  if (add.getVariable() != this->m_variable) {
    throw std::runtime_error(
        std::string(__FUNCTION__) + ": " +
        " error monom assignement addition between different variable");
  }
  m_value += add.getValue();
}

void Monom::operator-=(const Monom &sub) {
  if (sub.getOrder() != this->m_order) {
    throw std::runtime_error(
        std::string(__FUNCTION__) + ": " +
        " error monom assignement substraction between different order");
  }
  if (sub.getVariable() != this->m_variable && !sub.getVariable().size() &&
      !m_variable.size()) {
    throw std::runtime_error(
        std::string(__FUNCTION__) + ": " +
        " error monom assignement substraction between different variable");
  }
  m_value -= sub.getValue();
}

Monom Monom::abs() const {
  std::string varName = this->getVariable();
  std::size_t order = this->getOrder();
  double value = std::abs(this->getValue());
  return Monom(varName, order, value);
}

bool Monom::operator==(const Monom &check) {
  if (check.getOrder() == this->getOrder() &&
      check.getVariable() == this->getVariable() &&
      check.getValue() == this->getValue())
    return true;
  return false;
}

bool Monom::operator!=(const Monom &check) {
  if (check.getOrder() != this->getOrder() ||
      check.getVariable() != this->getVariable() ||
      check.getValue() != this->getValue())
    return true;
  return false;
}

void Monom::extractValue(const std::string &input) {
  int valueIndex = findUniqueOf(input, '*');
  if (valueIndex == MULTIPLE_DEFINITION) {
    throw std::runtime_error(std::string(__FUNCTION__) + ": " +
                             " too many '*' in this monom: " + input);
  }

  // index of m_variable in the input
  int varIndex = findUniqueOf(input, m_variable[0]);

  // handle 222X^2
  if (valueIndex == NOT_FOUND && varIndex != NOT_FOUND &&
      input.substr(0, varIndex).size() > 0) {
    m_value = convertStringToDouble(input.substr(0, varIndex));
  }
  // handle 222
  else if (valueIndex == NOT_FOUND && varIndex == NOT_FOUND) {
    m_value = convertStringToDouble(input);
  }
  // handle X^2
  else if (valueIndex == NOT_FOUND && findUniqueOf(input, '^') > 0) {
    m_value = 1;
  }
  // handle X3 (considered as false)
  else if (valueIndex == NOT_FOUND && input.size() > 1) {
    throw std::runtime_error(std::string(__FUNCTION__) + ": " +
                             " wrong placement of a value in this monom" +
                             input);
  }
  // handle X
  else if (valueIndex == NOT_FOUND) {
    m_value = 1;
  } else if (valueIndex != NOT_FOUND) {
    auto valueString = input.substr(0, valueIndex);
    if (valueString.size() == 0) {
      throw std::runtime_error(std::string(__FUNCTION__) + ": " +
                               "value is empty in this monom: " + input);
    }

    m_value = convertStringToDouble(valueString);
  } else {
    std::cerr << std::string(__FUNCTION__) << ": "
              << "error in the value extraction" << std::endl;
  }
}

void Monom::extractOrder(const std::string &input) {
  int expIndex = findUniqueOf(input, '^');
  if (expIndex == MULTIPLE_DEFINITION) {
    throw std::runtime_error(std::string(__FUNCTION__) + ": " +
                             " too many '^' in this monom: " + input);
  }

  int varIndex = findUniqueOf(input, m_variable[0]);
  if (varIndex == MULTIPLE_DEFINITION) {
    throw std::runtime_error(std::string(__FUNCTION__) + ": " +
                             " variable name can be just a single char.");
  } else if (varIndex == NOT_FOUND && expIndex != NOT_FOUND) {
    throw std::runtime_error(
        std::string(__FUNCTION__) + ": " +
        " variable name is missing in this monom: " + input);
  }

  if (expIndex == NOT_FOUND && varIndex == NOT_FOUND) {
    m_order = 0;
  } else if (expIndex == NOT_FOUND && varIndex != NOT_FOUND) {
    m_order = 1;
  } else if (expIndex != NOT_FOUND) {
    auto orderString = input.substr(expIndex + 1);
    if (orderString.size() == 0) {
      throw std::runtime_error(std::string(__FUNCTION__) + ": " +
                               "exponential is empty in this monom: " + input);
    }
    m_order = convertStringToInt(orderString);
  } else {
    std::cerr << std::string(__FUNCTION__) << ": "
              << "error in the order extraction" << std::endl;
  }
}

void Monom::parseMonom(const std::string &input, char sign) {
  bool defaultVariable = false;
  char varName = findVariableName(input);

  // if the variable name is undefine, it's set to the default one ('x')
  if (varName == 0) {
    varName = m_variable[0];
    defaultVariable = true;
  }

  // find the index of the variable, the value & the expenontial
  int varIndex = findUniqueOf(input, varName);

  if (varIndex == MULTIPLE_DEFINITION) {
    throw std::runtime_error(std::string(__FUNCTION__) + ": " +
                             " variable name can be just a single char.");
  }
  if (!defaultVariable)
    m_variable = std::string(1, varName);

  extractValue(input);
  extractOrder(input);

  if (sign == '-')
    m_value *= -1;
}

std::string Monom::monomAsString() const {
  return std::string(std::to_string(m_value) + " * " + m_variable + "^" +
                     std::to_string(m_order));
}

std::string Monom::getVariable() const { return (m_variable); }

std::size_t Monom::getOrder() const { return (m_order); }

double Monom::getValue() const { return (m_value); }

void Monom::setVariable(std::string &newVar) { m_variable = newVar; }

void Monom::setValue(double newValue) { m_value = newValue; }
