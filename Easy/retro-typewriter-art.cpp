#include <algorithm>
#include <bits/stdc++.h>

static void trim(std::string &s)
{
    s.erase(std::begin(s), std::find_if(std::begin(s), std::end(s), [](int ch) {
        return !std::isspace(ch);
    }));

    s.erase(std::find_if(std::rbegin(s), std::rend(s), [](int ch) {
        return !std::isspace(ch);
    }).base(), std::end(s));
}

static std::vector<std::string> split(std::string s, const std::string& sep)
{
   std::vector<std::string> res;
   size_t                   pos{ 0 };

   while ( std::string::npos != (pos = s.find(sep)) ) {
       res.emplace_back(s.substr(0, pos));
       s.erase(0, pos + std::size(sep));
   }

   if ( !std::empty(s) ) res.emplace_back(s);
   return res;
}

static void typewrite(std::string& line) {

    static const std::map<std::string, char> abbrevs = { 
        { "sp", ' ' }, { "bS", '\\' }, { "sQ", '\'' }, { "nl", '\n' }
    };

    std::cerr << "line : " << line << '\n';

    ::trim(line);
    if ( std::empty(line) ) { std::cout<< '\n'; return; }
    
    for ( auto& chunk : ::split(line, " ") ) {
        int         nb;
        std::string val;
        auto        first_non_digit = std::find_if(std::begin(chunk),
                                                   std::end(chunk),
                                                   [](char c){ return !std::isdigit(c); });
        if ( std::end(chunk) == first_non_digit ) {
            nb  = stoi( std::string(std::begin(chunk), std::end(chunk) -1));
            val = chunk.back();
        } else {
            nb  = std::stoi(chunk.substr(0, *first_non_digit));
            val = std::string(first_non_digit, std::end(chunk) );
        }

        std::cout << std::string(nb, ( std::end(abbrevs) != abbrevs.find(val) ) ? abbrevs.at(val) : val[0]); 
    }
    std::cout << '\n';
}

int main()
{
    std::string receipe;
    getline(std::cin, receipe);

    std::cerr << "receipe: " << receipe << '\n';

    for ( auto& line : ::split(receipe, "nl") )
        typewrite(line);

}