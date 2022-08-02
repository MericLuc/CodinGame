#include <bits/stdc++.h>

typedef std::string SIG;

int main()
{
    int         n, m;
    std::string so, s1, s2, op, val;

    std::unordered_map<SIG, SIG>                             cache;
    std::unordered_map<SIG, std::function<bool(bool, bool)>> ops = 
    {
        {"AND",  [](bool a, bool b){return   a & b;  }},
        {"OR",   [](bool a, bool b){return   a | b;  }},
        {"XOR",  [](bool a, bool b){return   a ^ b;  }},
        {"NAND", [](bool a, bool b){return !(a & b); }},
        {"NOR",  [](bool a, bool b){return !(a | b); }},
        {"NXOR", [](bool a, bool b){return !(a ^ b); }},
    };

    std::cin >> n >> m;
    for (int i = 0; i < n; ++i)
        std::cin >> so >> cache[so];

    for (int i = 0; i < m; ++i) {
        std::cin >> so >> op >> s1 >> s2;
        std::cout << so << " ";
        for (int j = 0; j < cache[s1].size(); ++j)
            std::cout << (ops[op](cache[s1][j] == '-', cache[s2][j] == '-') ? '-' : '_');
        std::cout << '\n';
    }
}