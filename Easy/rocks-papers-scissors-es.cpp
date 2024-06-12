#include <bits/stdc++.h>
#include <iterator>

typedef enum { ROCK, PAPER, SCISSORS } MOVE;

static const std::map<std::string, MOVE> movesMap{ 
    { "Rock", ROCK }, { "Paper", PAPER }, { "Scissors", SCISSORS } };

struct Player { 
    MOVE _move{ ROCK };
    Player( const std::string& input = "") {
        if ( std::end(movesMap) != movesMap.find(input) ) { _move = movesMap.at(input); }
    }
};

std::string move2str(const MOVE& mv) noexcept { 
    switch ( mv ) {
        case ROCK     : return "Rock";
        case PAPER    : return "Paper";
        case SCISSORS : return "Scissors";
    }
}

int                 nbPlayers;
std::vector<Player> players;

int getScore(int startIdx, MOVE move) noexcept {
    int curIdx{ startIdx }, endIdx{ startIdx == 0 ? nbPlayers - 1 : startIdx - 1}, score{ 0 };

    while ( curIdx != endIdx ) {
        switch (players.at(curIdx)._move ) {
            case ROCK:
                switch(move) {
                    case ROCK: goto draw;
                    case PAPER: goto win;
                    case SCISSORS: goto lose;
                }
            case PAPER:
                switch(move) {
                    case ROCK: goto lose;
                    case PAPER: goto draw;
                    case SCISSORS: goto win;
                }
            case SCISSORS:
                switch(move) {
                    case ROCK: goto win;
                    case PAPER: goto lose;
                    case SCISSORS: goto draw;
                }
        }

        draw:
            if ( 0 == score )
                goto lose;
            goto next;
        lose:
            break;
        win:
            score++;
            goto next;
        next:
            curIdx = (curIdx + 1) % nbPlayers;
    }
    return score;
}

int main() {
    std::string input;
    std::cin >> nbPlayers; std::cin.ignore();

    players = std::vector<Player>( nbPlayers );
    for ( int i{ 0 }; i < nbPlayers; ++i ) {
        std::getline(std::cin, input);
        players[i] = Player(input);
    }

    int  bestIdx { 0    }, bestScore{ -1 };
    MOVE bestMove{ ROCK };
    for     ( int i{ 0 }   ; i < nbPlayers; ++i ) {
        for ( int j{ ROCK }; j <= SCISSORS; ++j ) {
            if ( auto curScore{ getScore(i, static_cast<MOVE>(j)) }; curScore > bestScore ) {
                bestIdx = i, bestScore = curScore, bestMove = static_cast<MOVE>(j);
            }     
        }
    }

    std::cout << move2str(bestMove) << '\n' << bestIdx << std::endl;
}