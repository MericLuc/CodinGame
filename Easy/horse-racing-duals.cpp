#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

int main()
{
    std::istream_iterator<int> it(std::cin ), eos;
    std::vector<int>           in(++it, eos);

    std::sort               ( in.begin(), in.end()             );
    std::adjacent_difference( in.begin(), in.end(), in.begin() );

    std::cout << (*std::min_element(in.begin(), in.end())) << std::endl;
}