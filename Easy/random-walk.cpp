#include <bits/stdc++.h>

typedef std::pair<int, int> Pos;

template <typename T,typename U>                                                   
std::pair<T,U>& operator+=(std::pair<T,U> & l,const std::pair<T,U> & r) {   
    l.first += r.first;
    l.second += r.second; 

    return l;                                
} 

int main()
{
    int a, b, m, res{ 0 }, D{0};
    const std::array<Pos, 4> moves{ { {0, 1}, {0, -1}, {-1, 0}, {1, 0} } };
    const Pos origin{0,0};
    Pos curPos{origin};
    
    std::cin >> a >> b >> m; std::cin.ignore();

    do {
        D = ( a * D + b ) % m;
        curPos += moves[D%4];
        ++res;
    } while ( origin != curPos );

    std::cout << res << std::endl;
}