#include "../inc/parsing.h"
#include "../inc/Monom.h"
#include "../inc/Polynom.h"
#include <string>
#include <algorithm>

void handleInput(std::string& input)
{
    std::string::iterator end_pos = std::remove(input.begin(), input.end(), ' ');
    input.erase(end_pos, input.end());

    std::cout << input<< std::endl;

    int equal = foundOccurenceOf(input, '=');
    std::vector<std::pair<std::string, char> > leftMonoms = getMonoms(input.substr(0, equal));
    // std::vector<std::string> monoms = splitWithDelim(leftPart, "*");
    std::vector<Monom> vecMonoms;
    for (auto& token : leftMonoms){
        // std::cout << token.first << " sign:"<< token.second << std::endl;
        vecMonoms.emplace_back(Monom(token.first, token.second));
    }
    Polynom left(vecMonoms);
    left.printPolynom();
    return;
}

std::vector<std::pair<std::string, char> > getMonoms(std::string input)
{
    std::vector<std::pair<std::string, char> > monoms;
    int size = input.size();
    int lastMonom = 0;
    char lastSign = '+';

    for (int i = 0; i < size; i++){
        if (i == 0 && (input[i] == '+' || input[i] == '-'))
        {
            lastSign = static_cast<char>(input[i]);
            lastMonom++;
            continue;
        }
        if ((input[i] == '+' || input[i] ==  '-') && lastMonom == i)
        {
            std::cerr << "getMonoms: too many sign in the formula" << std::endl;
            exit(1);
        }

        if (i + 1 == size)
        {
            monoms.push_back({input.substr(lastMonom, i - lastMonom + 1), lastSign});
            return monoms;
        }
        if (input[i] == '+' || input[i] == '-'){
            monoms.push_back({input.substr(lastMonom, i - lastMonom), lastSign});
            lastSign = static_cast<char>(input[i]);
            lastMonom = i + 1;
        }

    }
    return (monoms);
}

int foundOccurenceOf(const std::string& input, char target)
{

    std::size_t targetIndex = input.find_first_of(target);
    if (targetIndex == std::string::npos){
        std::cerr << "Wrong polynom: missing '=' in the formula" << std::endl;
        exit(1);
    }

    if (targetIndex != input.find_last_of(target))
    {
        std::cerr << "Wrong polynom: multiple equal are found in this polynom" << std::endl;
        exit(1);
    }

    return targetIndex; 
}

std::vector<std::string> splitWithDelim(std::string in, std::string delim = "+")
{
    std::vector<std::string> tokens;
    std::string item;
    size_t pos = 0;

    while (true){
        pos = in.find(delim);
        if (pos == std::string::npos){
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

//je t'aime <3
// std::vector<std::string> splitWithDelim(std::string in, std::string delim = "+")
// {
//     std::vector<std::string> tokens;
//     std::string item;
//     size_t pos = 0;

//     while (in.substr(0, delim.length()) == delim)
//         in.erase(0, delim.length());
//     while (pos < in.size() && pos != std::string::npos) {
//         pos = in.find(delim);
//         item = in.substr(0, pos);
//         if (item.length() && item != delim) 
//             tokens.push_back(item);
//         // std::cout << "pos: " << pos << " in size: " << in.size() << std::endl; 
//         in.erase(0, pos + delim.length());
//     }
//     return tokens;
// }

// std::vector<std::string> splitWithDelim(std::string input, std::string delim = "+")
// {
//     std::vector<std::string> tokens;
//     std::string item;
//     size_t pos = 0;

//     while ()
// }