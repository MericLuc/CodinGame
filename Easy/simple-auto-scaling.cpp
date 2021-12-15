#include <bits/stdc++.h>

int main()
{
    int S, M, nb;
    std::cin >> S >> M;

    std::stringstream ss;
    std::vector<int>  srvs(S, 0), cap{srvs};

    for (auto& capacity : cap) std::cin >> capacity; 

    for (auto i = 0; i < M; ++i) {
        ss.str(std::string());
        for (auto j = 0; j < S; ++j) {
            std::cin >> nb;
            nb = ceil(nb / static_cast<double>(cap[j])); // Services can handle at least 1 client
            ss << nb - srvs[j] << " ";
            srvs[j] = nb;
        }
        auto res{ ss.str() };
        res.pop_back();
        std::cout << res << "\n";
    }
}