#include <bits/stdc++.h>

#define SIZE 6

int main()
{
    int fires{ 0 }, trees{ 0 }, to_cut{ 0 };
    std::vector<std::string> grid{ std::istream_iterator<std::string>(std::cin), 
                                   std::istream_iterator<std::string>()};
    std::set< std::pair<int, int> > firesList{};

    for (const auto& line : grid) 
        std::cerr << line << '\n';

    for     ( int i = 0; i < SIZE; ++i )
        for ( int j = 0; j < SIZE; ++j ) {
            if      ( '*' == grid[i][j] ) ++fires, firesList.insert({i,j});
            else if ( '#' == grid[i][j] ) ++trees;
        }

    if      ( !fires ) { std::cout << "RELAX\n";    return EXIT_SUCCESS; }
    else if ( !trees ) { std::cout << "JUST RUN\n"; return EXIT_SUCCESS; }

    for ( const auto& f : firesList )
        for     ( int i = f.first - 2;  i <= f.first + 2;  ++i)
            for ( int j = f.second - 2; j <= f.second + 2; ++j) {
                if ( i < 0 || i >= SIZE || j < 0 || j >= SIZE ) continue;
                if ( auto& cell = grid[i][j]; '#' == cell     ) { cell = '='; ++to_cut; }
            }

    std::cout << ( (to_cut == trees) ? "JUST RUN" : std::to_string(to_cut)) << '\n';
}