#include <iostream>
#include <string>

std::string nextGrowing( std::string p_num ) {

    for ( int c1 = p_num.size() -1; c1 >= 0; c1-- ) {

        if ( p_num[c1] != '9' ) {
            p_num[c1]++;
            for ( int c2 = c1 + 1; c2 < p_num.size(); c2++ ) {
                p_num[c2] = '0';
            }
            break;
        }

        if ( c1 == 0 ) {
            for ( int c2 = 0; c2 < p_num.size(); c2++ ) {
                p_num[c2] = '0';
            }
            p_num.insert(0, 1, '1');
        }
    }

    char  l_cur{ p_num[0] };
    bool  l_did{ false    };
    for ( auto& c : p_num ) {
        if ( c < l_cur || l_did ) { c = l_cur; l_did = true;  }
        l_cur = c;
    }

    return p_num;
}

int main()
{
    std::string N;
    std::getline(std::cin, N);

    std::cout << nextGrowing(N) << std::endl;
}

/*
// "Cheating" solution
// i.e. Converting input string to integer

#include <iostream>
#include <string>
#include <algorithm>

int main() {
    unsigned long long n;
    std::cin >> n;
    n++;

    auto s = std::to_string(n);
    auto f = std::adjacent_find(std::begin(s), std::end(s),
        [](auto a, auto b){ return a>b; });
    if (f != std::end(s))
        std::fill(std::next(f), std::end(s), *f);

    std::cout << s << std::endl;
}
*/