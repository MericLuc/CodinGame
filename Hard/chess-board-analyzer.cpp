#include <bits/stdc++.h>

std::map<char, std::vector<std::pair<int, int>>> dir = {
    {'K', {{ -1, -1}, { -1, 0}, { -1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}},
    {'Q', {{ -1, -1}, { -1, 0}, { -1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}},
    {'R', {{ -1, 0}, {0, -1}, {0, 1}, {1, 0}}},
    {'B', {{ -1, -1}, { -1, 1}, {1, -1}, {1, 1}}},
    {'P', {{ -1, -1}, { -1, 1}, {1, -1}, {1, 1}}},
    {'N', {{ -2, -1}, { -2, 1}, { -1, -2}, { -1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}}}
};

struct Piece {
    char pl, type;
    int  y, x;

    Piece(int _y = 0, int _x = 0, char p = ' ', char t = ' ') : y(_y), x(_x), pl(p),
        type(t) {}

    bool Move(int d, int &y, int &x) {
        y += (dir[toupper(type)][d].first);
        x += (dir[toupper(type)][d].second);

        return (y >= 0 && x >= 0 && y < 8 && x < 8);
    }
};

std::vector<Piece> pieces;

bool InCheck(Piece king, std::vector<std::string>& grid) {
    for (auto piece : pieces) {
        if (piece.pl == king.pl) continue;

        for (int d = 0; d < std::size(dir[toupper(piece.type)]); ++d) {
            int ny{ piece.y }, nx{ piece.x };

            while (piece.Move(d, ny, nx)) {
                if (grid[ny][nx] == king.type) return true;
                if (grid[ny][nx] != '.'      ) break;
                if ( std::string::npos != std::string("NPKnpk").find(piece.type) ) break;
            }
        }
    }
    return false;
}

bool Solve(Piece king, std::vector<std::string>& grid) {
    std::vector<std::pair<int, int>> moves = {{king.y, king.x}};

    for (int d = 0; d < std::size(dir['K']); ++d) {
        int ny{ king.y }, nx{ king.x };

        if (king.Move(d, ny, nx) &&
                (isupper(grid[ny][nx]) != isupper(king.type))) moves.push_back({ny, nx});
    }

    for (const auto& [ y, x ] : moves) {
        grid[y][x] = king.type;
        if (!InCheck(king, grid)) return false;
        grid[y][x] = '.';
    }
    return true;
}

int main() {
    Piece white, black;
    auto grid = std::vector<std::string>(std::istream_iterator<std::string>
                                         (std::cin), {});
    for     (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isalpha( grid[i][j])) {
                Piece piece(i, j, std::string("BW")[isupper( grid[i][j])],  grid[i][j]);

                pieces.push_back(piece);

                if      (piece.type == 'K') white = piece;
                else if (piece.type == 'k') black = piece;
            }
        }
    }

    grid[white.y][white.x] = '.';
    grid[black.y][black.x] = '.';

    std::cout << ( Solve(white, grid) ? 'B' : ( Solve(black, grid) ? 'W' : 'N') );
}