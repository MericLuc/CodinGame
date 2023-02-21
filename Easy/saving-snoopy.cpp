#include <bits/stdc++.h>

int main()
{
    int                  n, mlen;
    std::string          swap, msg, dcd;
    std::map<char, char> repl;

    std::cin >> n; std::cin.ignore();

    for ( auto i{ 0 }; i < n ; ++i )
        getline(std::cin, swap), repl[swap.front()] = swap.back();

    std::cin >> mlen; std::cin.ignore();
    getline(std::cin, msg);

    std::deque<char> queue;
    for ( auto it{ std::cbegin(msg) }; std::cend(msg) != it; ++it) {
        switch(*it) {
            case '+' : break;
            case '*' : {
                auto lc{ queue.back() };
                if ( std::end(repl) != repl.find(lc) ) lc = repl[lc];
                dcd += lc;
                queue.pop_back();
            } break;
            case '#' : { 
                for ( auto i{ 0 }; i < (int)(*(it + 1) - '0'); ++i )
                    queue.pop_back();
                ++it;
            }  break;
            case '%' : {
                std::deque<char> shuffled;
                for ( auto i{ 0 }; i < std::size(queue); i += 2 )
                    shuffled.push_back(queue[i]);               
                for ( auto i{ 1 }; i < std::size(queue); i += 2 )
                    shuffled.push_back(queue[i]);
                queue = shuffled;
            } break;
            default  : queue.push_back(*it); break;
        }
    }

    std::istringstream       iss(dcd);
    std::string              curLine, curWord;
    while (iss >> curWord) {        
        if ( std::size(curLine) + std::size(curWord) < 75 ) {
            curLine += std::empty(curLine) ? curWord : std::string(' ' + curWord);
        } else {
            std::cout << curLine << '\n';
            curLine = curWord;
        }
    }

    if ( !std::empty(curLine) )
        std::cout << curLine << '\n'; 
}