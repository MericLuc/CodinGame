#include <bits/stdc++.h>

int main () {
    std::string buffer, wrd{};
    std::getline(std::cin, buffer);

    for ( int i=0; i<26; ++i ) {
        auto decoded{ buffer };
        std::transform(std::begin(buffer), std::end(buffer), std::begin(decoded), 
                       [&](char c){ return !isupper(c) ? c : char((c + i) % 26 + 'A'); });
        
        std::istringstream ss(decoded);
        while (std::getline(ss, wrd, ' '))
            if ( wrd == "CHIEF" ) { std::cout << decoded << "\n"; exit(EXIT_SUCCESS); }        
    }
    std::cout << "WRONG MESSAGE\n";
}