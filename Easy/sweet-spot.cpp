#include <bits/stdc++.h>

int main()
{
    std::istream_iterator<std::string> it(std::cin), eos;
    std::vector<std::string> in(++it, eos), out{in};

    const auto H{ std::size(in) }, W{ std::size(in[0]) };

    std::stack< std::pair<int, int> > bbombs;
    std::set  < std::pair<int, int> > done;

    for     (int r = 0; r < H; ++r)
        for (int c = 0; c < W; ++c)
            switch ( in[r][c] )
            {
                case 'A':
                    for ( int ii = -3; ii <= 3; ++ii )
                        for ( int jj = -3; jj <= 3; ++jj )
                            if ( ((ii + r < H) && (ii + r >= 0)) && 
                                 ((jj + c < W) && (jj + c >= 0)) && 
                                 (ii || jj) ) {
                                 char cval = '4' - std::max(abs(ii),abs(jj));
                                 if      ( out[r + ii][c + jj] < cval ) out[r + ii][c + jj] = cval; 
                                 else if ( out[r + ii][c + jj] == 'B' ) bbombs.push({r + ii, c + jj});
                            }
                break;
                case 'H':
                    for ( int ii = -3; ii <= 3; ++ii )
                        for ( int jj = -3; jj <= 3; ++jj )
                            if ( ((ii + r < H) && (ii + r >= 0)) && 
                                 ((jj + c < W) && (jj + c >= 0)) && 
                                 (ii || jj) ) {
                                if      ( out[r + ii][c + jj] <  '5' ) out[r + ii][c + jj] = '5'; 
                                else if ( out[r + ii][c + jj] == 'B' ) bbombs.push( { r + ii, c + jj } );
                            }
                break;
                default : break;
            }
    
    while ( !std::empty(bbombs) ) {
        auto [r, c] = bbombs.top();
        bbombs.pop();
        done.insert( {r, c} );

        for ( int ii = 1; ii <= 3; ++ii ) {
            char val  = 4 - ii + '0';
            if (r + ii <  H) {
                if      ( out[r + ii][c     ] < val  ) out[r + ii][c     ] = val;
                else if ( out[r + ii][c     ] == 'B' && 
                         !done.count({r + ii, c    })) bbombs.push({r + ii, c       });
            }
            if (r - ii >= 0) {
                 if     ( out[r - ii][c     ] < val  ) out[r - ii][c     ] = val;
                else if ( out[r - ii][c     ] == 'B' &&
                         !done.count({r - ii, c    })) bbombs.push({r - ii, c       });
            }
            if (c + ii <  W) {
                if      ( out[r     ][c + ii] < val  ) out[r     ][c + ii] = val;
                else if ( out[r     ][c + ii] == 'B' &&
                         !done.count({r    , c + ii})) bbombs.push({r     , c +  ii });
            }
            if (c - ii >= 0) {
                if      ( out[r     ][c - ii] < val  ) out[r     ][c - ii] = val;
                else if ( out[r     ][c - ii] == 'B' &&
                         !done.count({r    , c - ii})) bbombs.push({r     , c -  ii });
            }
        }
    }

    for ( auto& line : out ) std::cout << line << '\n';
}