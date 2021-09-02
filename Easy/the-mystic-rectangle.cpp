#include <bits/stdc++.h>

int main()
{
    int         x,   y,   u,   v;
    std::cin >> x >> y >> u >> v;

    auto dx{std::min((200+(x-u)%200)%200,(200+(u-x)%200)%200)}, 
         dy{std::min((150+(y-v)%150)%150,(150+(v-y)%150)%150)};

    std::cout << std::fixed << std::setprecision(1) << (dx*.3 + dy*.4 - std::min(dx,dy)*.2) << "\n";
}