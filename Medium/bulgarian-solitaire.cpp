#include <bits/stdc++.h>

int main()
{
    std::istream_iterator<int>      it(std::cin), eos;
    std::vector<int>                v(++it, eos);
    std::vector< std::vector<int> > save;

    while ( true ) {
        v.erase( std::remove( std::begin(v), std::end(v), 0 ), std::end(v) );
        std::sort( std::begin(v), std::end(v) );

        if ( auto it = std::find( std::begin(save), std::end(save), v); it != std::end(save) ) {
            std::cout << std::size(save) - std::distance( std::begin(save), it ) << "\n";
            break;
        }

        save.emplace_back(v);
        std::for_each( std::begin(v), std::end(v), [](auto& num){ --num; });
        v.push_back( std::size(v) );;
    }
}