#include <bits/stdc++.h>

std::string solve(std::string_view s, std::string_view answer) noexcept {

    enum class EValState : char {
        ABSENT = 'X', MISPLACED = 'O', CORRECT = '#'
    };

    std::string ret(std::size(answer), static_cast<char>(EValState::ABSENT));

    if ( std::size(s) != std::size(answer) )
        return ret;

    std::map<char, int> occCount, occInAnswer;
    for ( const auto& c : answer ) ++occInAnswer[c];

    for ( auto i{ 0 }; i < std::size(answer); ++i ) {
        const auto& curChar{ s.at(i) };

        if ( curChar != answer.at(i) )
            continue;
        
        ret[i] = static_cast<char>(EValState::CORRECT);
        ++occCount[curChar];
    }

    for ( auto i{ 0 }; i < std::size(answer); ++i ) {
        const auto& curChar{ s.at(i) };

        if ( curChar == answer.at(i) || occCount[curChar] >= occInAnswer[curChar])
            continue;

        ret[i] = static_cast<char>(EValState::MISPLACED);
        ++occCount[curChar];
    }

    return ret;
}

int main()
{
    std::string answer, attempt;
    getline(std::cin, answer);

    std::cin.ignore(std::numeric_limits<int>::max(), '\n');

    while ( getline(std::cin, attempt) )
        std::cout << solve(attempt, answer) << '\n';
}