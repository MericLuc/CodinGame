#include <bits/stdc++.h>


int main()
{
    std::map< char, std::string > dic{};
    std::string                   row, mesg;
    int                           rows; 
    
    std::cin >> rows; std::cin.ignore();

    for ( int i = 0; i < rows; ++i ) {
        int j{ 0 };
        getline(std::cin, row);
        std::for_each( std::begin(row), std::end(row), [&dic, &i, &j](const auto& c){
            if ( !isspace(c) )
                dic[c] = std::to_string(i) + std::to_string(j++);
        });
    }

    getline(std::cin, mesg);
    for ( const auto& c : mesg )
        std::cout << dic[c];
    std::cout << "\n";
}
