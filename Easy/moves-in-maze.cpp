// from Remi

#include <iostream>

struct coord { int x, y, n; };
int main() {

    int w, h, x, y=-1;
    std::cin >> w >> h; std::cin.ignore();
    
    std::string g[h];
    for (int i=0; i<h; ++i) {
        getline(std::cin, g[i]);
        if (y == -1) x = g[i].find_first_of('S'), y = (std::string::npos != x) ? i : -1;
    }

    coord coords[1024];
    int len = 0, it = 0;
    g[y][x] = '0';
    coords[len++] = {x, y, 0};
    while (it < len) {
        int X = coords[it].x, Y = coords[it].y, N = coords[it].n+1;
        int X1 = (X+1)%w, X_1 = (X-1+w)%w, Y1 = (Y+1)%h, Y_1 = (Y-1+h)%h;
        char c = N<10 ? N+'0' : N-10+'A';
        if (g[Y  ][X1 ] == '.') g[Y  ][X1 ] = c, coords[len++] = {X1 , Y  , N};
        if (g[Y  ][X_1] == '.') g[Y  ][X_1] = c, coords[len++] = {X_1, Y  , N};
        if (g[Y1 ][X  ] == '.') g[Y1 ][X  ] = c, coords[len++] = {X  , Y1 , N};
        if (g[Y_1][X  ] == '.') g[Y_1][X  ] = c, coords[len++] = {X  , Y_1, N};
        ++it;
    }

    for (int i=0; i<h; ++i) std::cout << g[i] << '\n';
}