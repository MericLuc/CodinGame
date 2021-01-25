#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void printDbg( const std::vector< std::string>& p_grid ) {
    static int turn{1};
    std::cerr << "----- Turn " << turn++ << " -----\n";
    for ( const auto& line : p_grid ) { std::cerr << "\t" << line << "\n"; }
    std::cerr << "------------------\n";
}

int main()
{
    int h, w, nb, nb_int{0}, nb_mine{0}, turn{0};
    int dx[] = { -1, -1, -1,  0, 0,  1, 1, 1 };
    int dy[] = { -1,  0,  1, -1, 1, -1, 0, 1 };

    std::cin >> h >> w >> nb; std::cin.ignore();

    std::vector< std::string > grid{h};

    std::cerr << h << " " << w << " " << nb << "\n";

    for ( int i = 0; i < h; i++) { 
        getline( std::cin, grid[i] ); 
        nb_int += std::count( std::begin(grid[i]), std::end(grid[i]), '?' );
    }


    while ( nb_mine < nb ) {

        if ( nb_int == nb - nb_mine ) {
            for ( int i = 0; i < h; ++i )
                std::replace( std::begin(grid[i]), std::end(grid[i]), '?', 'X' );
            nb_mine = nb; 
            nb_int  = 0;
        }
        
        if ( nb_mine != nb ) {
            for ( int i = 0; i < h; ++i ) {
                for ( int j = 0; j < w; ++j ) {
                    if ( grid[i][j] >= '1' && grid[i][j] <= '8' ) 
                    {
                        int nb_m{0}, nb_i{0};
                        for ( int d = 0; d < 8; ++d ) {
                            int x = j + dx[d];
                            int y = i + dy[d];

                            if ( x >= 0 && x < w && y >= 0 && y < h ) {
                                if      ( grid[y][x] == '?' ) ++nb_i;
                                else if ( grid[y][x] == 'X' ) ++nb_m;
                            }
                        }

                        if ( nb_m == grid[i][j] - '0' ) {
                            for ( int d = 0; d < 8; ++d ) {
                                int x = j + dx[d];
                                int y = i + dy[d];

                                if ( x >= 0 && x < w && y >= 0 && y < h && grid[y][x] == '?' ) {
                                    grid[y][x] = '.';
                                    --nb_int;
                                }
                            }
                        }
                        else if ( nb_m + nb_i == grid[i][j] - '0' ) {
                            for ( int d = 0; d < 8; ++d ) {
                                int x = j + dx[d];
                                int y = i + dy[d];

                                if ( x >= 0 && x < w && y >= 0 && y < h && grid[y][x] == '?' ) {
                                    grid[y][x] = 'X';
                                    --nb_int;
                                    ++nb_mine;
                                }
                            }
                        }
                    }
                }
            }
        }

        printDbg(grid);
    }

    for ( int col = 0; col < w; ++col )
        for ( int line = 0; line < h; ++line )
            if ( grid[line][col] == 'X' ) std::cout << col << " " << line << std::endl;
}