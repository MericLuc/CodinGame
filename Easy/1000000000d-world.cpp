#include <bits/stdc++.h>

std::vector<int> getVec(const std::string& str) {
    std::istringstream iss(str);

    return std::vector<int>((std::istream_iterator<int>(iss)),
                             std::istream_iterator<int>());
}

int main()
{
    std::string a, b;
    getline(std::cin, a);
    getline(std::cin, b);

    auto v1{ getVec(a) }, v2{ getVec(b) };
    int64_t ret{0}, n{0}, m{0}, count{0}, times{0};

    while( n < std::size(v1) )
    {
        times  = std::min(v1[n], v2[m]);
        v1[n] -= times;
        v2[m] -= times;
        count += times;
        ret   += times * v1[n+1] * v2[m+1];

        if ( v1[n] == 0 ) { n += 2; }
        if ( v2[m] == 0 ) { m += 2; }
    }
    std::cout << ret << "\n";
}
