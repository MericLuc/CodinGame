#include <bits/stdc++.h>

struct LinkedCell { int x, y; LinkedCell* prev; };

int main() {

    int w, h, x{ 0 }, y{ 0 }, len{ 0 }, it{ 0 };
    std::cin >> w >> h; std::cin.ignore();
    std::vector<std::string> grid{ std::istream_iterator<std::string>(std::cin), 
                                   std::istream_iterator<std::string>() };

    for ( ; y < h; ++y )
        if ( x = grid[y].find_first_of('S'); std::string::npos != x ) 
            break;

    LinkedCell path[512], *end = nullptr;
    path[len++] = {x, y, nullptr};
    
    while (!end) {
        LinkedCell* prev = &path[it];
        int X = prev->x, Y = prev->y;
        int X1 = (X+1)%w, X_1 = (X-1+w)%w, Y1 = (Y+1)%h, Y_1 = (Y-1+h)%h, X_d = Y%2 ? X1 : X_1;
        if (grid[Y][X1]=='E' || grid[Y][X_1]=='E' || grid[Y1][X]=='E' || grid[Y_1][X]=='E' || grid[Y1][X_d]=='E' || grid[Y_1][X_d]=='E')
            end=prev;
        else {
            if (grid[Y  ][X1 ]=='_') path[len++]={X1 , Y  , prev}, grid[Y  ][X1 ]=' ';
            if (grid[Y  ][X_1]=='_') path[len++]={X_1, Y  , prev}, grid[Y  ][X_1]=' ';
            if (grid[Y1 ][X  ]=='_') path[len++]={X  , Y1 , prev}, grid[Y1 ][X  ]=' ';
            if (grid[Y_1][X  ]=='_') path[len++]={X  , Y_1, prev}, grid[Y_1][X  ]=' ';
            if (grid[Y1 ][X_d]=='_') path[len++]={X_d, Y1 , prev}, grid[Y1 ][X_d]=' ';
            if (grid[Y_1][X_d]=='_') path[len++]={X_d, Y_1, prev}, grid[Y_1][X_d]=' ';
        }
        ++it;
    }

    while ( nullptr != end->prev )
        grid[end->y][end->x] = '.', end = end->prev;

    for     ( int i = 0; i < h; ++i ) {
        for ( int j = 0; j < w; ++j )
            if ( ' ' == grid[i][j] ) grid[i][j] = '_';
        std::cout << grid[i] << '\n';
    }
}
