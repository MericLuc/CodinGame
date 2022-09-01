#include <bits/stdc++.h>

size_t get_line_pos(const std::string& in, size_t pos, size_t lineNb) {
    if(0 == lineNb) return pos;
    return get_line_pos(in, in.find("\\n", pos) + 2,  lineNb-1);
}

struct Commit { 
    int         line, col;
    std::string val;

    static void insert(std::string& str, const Commit& c) {
        str.insert(get_line_pos(str, 0, c.line) + c.col, c.val);
    }
};

std::istream& operator>>(std::istream& is, Commit& in) { 
    char useless;
    is >> in.line >> useless >> in.col >> useless;
    getline(std::cin, in.val);
    return is;
}

int main()
{
    std::string s, line; getline(std::cin, s);
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');

    std::vector< Commit > commits{ std::istream_iterator<Commit>(std::cin),
                                   std::istream_iterator<Commit>() };
    std::sort( std::begin(commits), std::end(commits), [](const auto& a, const auto& b){
        return (a.line > b.line) || ( a.line == b.line && a.col > b.col);
     } );

    for (const auto& commit : commits )
        Commit::insert(s, commit);    

    std::cout << std::regex_replace(s, std::regex(R"(\\n)"), "\n") << '\n';
}