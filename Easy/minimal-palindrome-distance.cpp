#include <bits/stdc++.h>

int doTheJob(char str[], int sz) noexcept {
    static int res{ 0 };
    int s{ 0 }, e{ sz - 1 };
    while( s < e ) {
        if( str[s] != str[e] && ++res )
            return doTheJob(str + 1, sz - 1);
        s++, e--;
    }
    return res;
}

int main()
{
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    std::string s;
    getline(std::cin, s);

    std::cout << doTheJob(&s[0], std::size(s) );
}