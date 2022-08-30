#include <bits/stdc++.h>

int main(){
    int H, W;
    std::cin >> H >> W;

    double                     res{ 1 };
    std::vector< double >      probs;
    std::vector< std::string > grid{ std::istream_iterator<std::string>(std::cin), 
                                     std::istream_iterator<std::string>() };


    for    ( double y = 0; y < H; ++y ) 
        for( double x = 0; x < W; ++x )
          if( 'G' == grid[y][x] )
            probs.push_back( std::min(x, y)/( x*x + y*y + 1) );
    
    std::sort( std::begin(probs), std::end(probs) );
    
    for( int i = 0; i < std::size(probs); ++i ) {
        res *= 1 - probs[i];
        if( res < 0.6 ){ std::cout << i << '\n'; break; }
    }
}