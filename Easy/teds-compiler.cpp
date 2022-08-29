#include <bits/stdc++.h>

int main()
{
    std::string      line;
    int              ret{ 0 };
    std::stack<char> stk{   };

    getline(std::cin, line);

    for ( int i = 0; i < std::size(line); ++i ) {
        if ( '<' == line[i] ) stk.push('<');
        else {
            if ( stk.empty() ) break;
            stk.pop();
            if ( stk.empty() ) ret = i + 1;
        }
    }

    std::cout << ret << '\n';
}