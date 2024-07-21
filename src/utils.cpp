#include "../inc/utils.h"

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int gcd_of_n(std::vector<int> arr)
{
    if (arr.size() == 0)
        return 1;

    int result = *arr.begin();
    for (auto& value : arr)
        result = gcd(value, result);
    return result;
}