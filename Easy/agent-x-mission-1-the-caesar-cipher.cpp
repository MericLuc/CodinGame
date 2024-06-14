#include <bits/stdc++.h>

int main() {
    std::string     ciphertext, word, decoded, tmp;
    std::set<char>  delimiters{ ' ', ',', '.', '?', ';', ':', '!' };
    int             key{ 0 }, cmpt;

    getline(std::cin, ciphertext);
    std::cin >> word; std::cin.ignore();

    for ( key = 0; key < 96; ++key ) {
        decoded = tmp = ciphertext;
        cmpt    = 0;
        std::for_each(std::begin(decoded), std::end(decoded), [&](char& c) {
            c           = (( c - key - 32 + 95 ) % 95) + 32;
            tmp[cmpt++] = ( delimiters.count(c) ) ? ' ' : c;
        });

        std::istringstream iss(tmp);
        for ( const auto& w : std::vector<std::string>((std::istream_iterator<std::string>(iss)),
                                  std::istream_iterator<std::string>()) ) 
            if ( word == w ) goto end;
    }

end:
    std::cout << key << '\n' << decoded << std::endl;
}