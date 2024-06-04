#include <bits/stdc++.h>

bool isKangaroo(const std::string& s1, const std::string& s2) noexcept {
    int is1{ 0 }, is2{ 0 };

    while ( std::size(s1) > is1 ) {
        if ( s1[is1] == s2[is2]   ) is2++;
        if ( std::size(s2) == is2 ) return true;
        is1++;
    }
    return false;
}

int main() {
    std::cin.ignore(std::numeric_limits<int32_t>::max(), '\n');
    
    std::map<std::string /*kangaroo*/, std::set<std::string /*joey*/>> res;
    std::string                                                        input, output, word;
    while ( getline(std::cin, input) ) {
        input.erase(std::remove_if(std::begin(input), std::end(input), isspace), std::end(input));

        std::stringstream        ss{input};
        std::vector<std::string> synonyms{ };
        while (getline(ss, word, ',')) {
            synonyms.push_back(word);
        }
        std::sort(std::begin(synonyms), std::end(synonyms), [](const auto& s1, const auto& s2) {
            return ( std::size(s1) > std::size(s2) ) || ( ( std::size(s1) == std::size(s2) ) && ( s1 > s2 ) );
        });

        for     ( int i{ 0    }; i < std::size(synonyms); ++i ) {
            for ( int j{ i + 1}; j < std::size(synonyms); ++j ) {
                if ( isKangaroo(synonyms[i], synonyms[j]) ) {
                    res[synonyms[i]].insert(synonyms[j]);
                }
            }
        }
    }

    if ( std::empty(res) ) { 
        std::cout << "NONE" << std::endl; 
        return EXIT_FAILURE;  
    }

    for ( const auto& [kangaroo, joeysList] : res ) {
        std::stringstream ss;
        ss << kangaroo << ':';
        for ( const auto& joey : joeysList ) ss << ' ' << joey << ',';
        output = ss.str();
        if ( output.ends_with(',') ) { output.pop_back(); }

        std::cout << output << std::endl;
    }
    return EXIT_SUCCESS;
}