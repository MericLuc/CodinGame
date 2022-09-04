#include <bits/stdc++.h>

typedef enum { NUMS, OPS, EVS } MODS;

int main()
{
    std::vector<std::string> inputs{ ++std::istream_iterator<std::string>(std::cin),
                                       std::istream_iterator<std::string>() };
    std::string cur;
    double mem  { 0    }, useless;
    char   op   { ' '  };
    MODS   mode { NUMS };
    bool   start{ true };

    auto ops = [&op](double a, double b) {
        switch (op) {
            case '+' : return a + b;
            case '-' : return a - b;
            case 'x' : return a * b;
            case '/' : return a / b;
            default  : return b;
        }
    };

    for ( const auto& c : inputs ) {        
        if ( std::isdigit(c[0]) ) {
            if ( EVS == mode ) { mem = 0, cur.clear(), op = ' '; }
            if ( start       ) { start = false; cur.clear();     } 
            mode = NUMS;
            cur += c;
            std::cout << cur << '\n';
            continue;
        }
        else if ( "AC" == c ) {
            mem   = 0;
            op    = ' ';
            mode  = NUMS; 
            start = true;
            cur.clear();
        }
        else if ( "="  == c ) {
            mem   = ops(mem, std::stod(cur));
            mode  = EVS;
            start = true;
        }
        else {
            if ( NUMS == mode ) { mem = ops(mem, std::stod(cur)); start = true; }
            op   = c[0];
            mode = OPS;
        }

        if ( 0 == std::modf(mem, &useless) )
            std::cout << mem << '\n';
        else {
            std::string ret = std::to_string( round( mem * 1000.0 ) / 1000.0 );
            if ( auto it = std::find( std::begin(ret), std::end(ret), '.'); std::end(ret) != it ) {
                ret.erase(it + 4, std::end(ret));
                if ( size_t end = ret.find_last_not_of('0'); std::string::npos != end )
                    ret = ret.substr(0, end + 1);
                std::cout << ret << '\n';
            }
        }
    }
}