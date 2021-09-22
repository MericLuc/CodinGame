#include <bits/stdc++.h>

int main()
{
    int N; std::cin >> N; std::cin.ignore();
    std::vector<std::string> grid( N + 2, std::string(128, ' ') );

    const auto rtrim = [](std::string &s) {
    s.erase(std::find_if(std::rbegin(s), std::rend(s),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), std::end(s));
    };

    for (int i = 0; i < N; i++) { 
        std::string tmp;
        getline( std::cin, tmp ); 
        for ( int j = 0; j < std::size(tmp); ++j )
            if ( !isspace(tmp[j]) ) { grid[i][j]=tmp[j]; grid[i+1][j+1] = '-'; grid[i+2][j+2] = '`'; } 
    }

    for ( auto& s : grid ) { rtrim(s); std::cout << s << "\n"; }
}