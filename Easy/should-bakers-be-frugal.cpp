#include <bits/stdc++.h>

int main()
{
    float n, d;
    int   res_wasteful{ 0 }, res_frugal{ 0 };
    std::cin >> n >> d; std::cin.ignore();

    double biscuit_area = M_PI * (d*0.5) * (d*0.5);

    res_wasteful = floor(n/d) * floor(n/d);
    res_frugal   = floor( (n*n - d*d + biscuit_area) / biscuit_area );

    std::cout << res_frugal - res_wasteful << '\n';
}