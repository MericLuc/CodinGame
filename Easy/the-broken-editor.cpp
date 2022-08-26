#include <bits/stdc++.h>

int main()
{
    int         curs{ 0 };
    std::string in, out;
    getline(std::cin, in);

    std::for_each(std::begin(in), 
                  std::end(in), 
                  [&out, &curs](const auto& c) {
                      switch(c) {
                          case '<': if ( curs > 0 ) --curs; break;
                          case '>': if ( curs < std::size(out) ) ++curs; break;
                          case '-': if ( curs > 0 ) { out.erase(--curs, 1); } break;
                          default : out.insert(curs++, 1, c); break; 
                      }
                  });

    std::cout << out << '\n';
}