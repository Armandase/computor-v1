#include "../inc/parsing.h"

Polynom getMonomFromString(const std::string &str) {
  std::vector<std::pair<std::string, char>> vecStringMonom = getMonoms(str);
  std::vector<Monom> vecMonoms;
  for (auto &token : vecStringMonom) {
    vecMonoms.emplace_back(Monom(token.first, token.second));
  }
  Polynom result(vecMonoms);
  result.sortPolynom();
  return (result);
}

Polynom handleInput(std::string &input) {
  std::string::iterator end_pos = std::remove(input.begin(), input.end(), ' ');
  input.erase(end_pos, input.end());

  int equal = foundOccurenceOf(input, '=');
  std::string left(input.substr(0, equal));
  std::string right(input.substr(equal + 1));
  if (left.empty() || right.empty()) {
    throw std::runtime_error("Wrong polynom: missing a part in the formula");
  }

  Polynom leftPart = getMonomFromString(left);
  Polynom rightPart = getMonomFromString(right);

  // if (leftPart.getMaxOrder() > 2 || rightPart.getMaxOrder() > 2)
  //   throw std::runtime_error(
  //       std::string(__FUNCTION__) + ": " +
  //       "The polynomial degree is strictly greater than 2, I can't solve.");

  leftPart.toNull(rightPart);
  // handle the case where there is just X^0 and the values between left and
  // right are the same
  if (leftPart.getMaxOrder() == 0 && rightPart.getMaxOrder() == 0 &&
      rightPart.getVecMonoms().size() == 1 &&
      leftPart.getVecMonoms().size() == 1 &&
      leftPart.getVecMonoms().front() == rightPart.getVecMonoms().front())
    return (Polynom());
  return leftPart;
}

std::vector<std::pair<std::string, char>> getMonoms(std::string input) {
  std::vector<std::pair<std::string, char>> monoms;
  int size = input.size();
  int lastMonom = 0;
  char lastSign = '+';

  for (int i = 0; i < size; i++) {
    if (i == 0 && (input[i] == '+' || input[i] == '-')) {
      lastSign = static_cast<char>(input[i]);
      lastMonom++;
      continue;
    }
    if ((input[i] == '+' || input[i] == '-') && lastMonom == i) {
      throw std::runtime_error("getMonoms: too many sign in the formula");
    }

    if (i + 1 == size) {
      monoms.push_back({input.substr(lastMonom, i - lastMonom + 1), lastSign});
      return monoms;
    }
    if (input[i] == '+' || input[i] == '-') {
      monoms.push_back({input.substr(lastMonom, i - lastMonom), lastSign});
      lastSign = static_cast<char>(input[i]);
      lastMonom = i + 1;
    }
  }
  return (monoms);
}

int foundOccurenceOf(const std::string &input, char target) {

  std::size_t targetIndex = input.find_first_of(target);
  if (targetIndex == std::string::npos) {
    throw std::runtime_error("Wrong polynom: missing '=' in the formula");
  }

  if (targetIndex != input.find_last_of(target)) {
    throw std::runtime_error(
        "Wrong polynom: multiple equal are found in this polynom");
  }

  return targetIndex;
}

std::vector<std::string> splitWithDelim(std::string in,
                                        std::string delim = "+") {
  std::vector<std::string> tokens;
  std::string item;
  size_t pos = 0;

  while (true) {
    pos = in.find(delim);
    if (pos == std::string::npos) {
      if (in.length() && in != delim)
        tokens.push_back(in);
      break;
    }
    item = in.substr(0, pos);
    in = in.substr(pos + delim.length());
    if (item.length() && item != delim)
      tokens.push_back(item);
  }

  return tokens;
}