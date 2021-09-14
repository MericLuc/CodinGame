#include <bits/stdc++.h>

int main()
{
    std::stringstream          ss;
    std::istream_iterator<int> it(std::cin), eos;
    std::vector<int>           v (it, eos);
    std::string                res{""};

    for ( int i = 2; i < std::size(v); ++i )
        res += ( i % 2 ) ? std::string(v[i],' ') : std::string(v[i],'*');

    std::for_each( std::begin(res), std::end(res), [&v, &ss](auto c){
        static int cmpt = 0;
        if ( cmpt % v[0] == 0 ) { cmpt = 0; ss << "|\n|"; }
        ss << c;
        ++cmpt;
    });

    std::cout << ss.str().substr(2) << "|\n";
}