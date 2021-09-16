#include <bits/stdc++.h>

typedef std::vector<std::string>       TREASURE_MAP;
typedef std::vector<std::vector<bool>> VISITED_MAP;

std::vector< std::pair<int, int> > dirs = { {-1,0}, {1,0}, {0,-1}, {0,1} };

bool inRange  (const TREASURE_MAP& m, int i, int j) {
    return (i >= 0 && i < (int)m.size()) && (j >= 0 && j < (int)m[0].size());
}

bool isCandidate(const TREASURE_MAP& m, const VISITED_MAP& v, int i, int j) {
    return inRange(m, i, j) && (m.at(i).at(j)!='#') && !v.at(i).at(j);
}

void getStartingPos(TREASURE_MAP& m, int& i, int& j) {
    for ( int row = 0; row < (int)m.size(); row++ )
        for ( int col = 0; col < (int)m.at(0).size(); col++ )
            if ( m.at(row).at(col) == 'X' ) { i = row; j = col; m[i][j] = ' '; break; }
}

int backtrack( const TREASURE_MAP& m, VISITED_MAP& v, int i, int j, int curSum ) {
    if ( m[i][j] != ' ' ) { curSum += m[i][j] - '0'; }
    v[i][j] = true;

    std::vector<int> tmp;
    for ( auto& d: dirs )
    {
        int nxt_i(i + d.first), nxt_j(j + d.second);
        if ( isCandidate(m, v, nxt_i, nxt_j) ) { tmp.push_back(backtrack(m, v, nxt_i, nxt_j, curSum) ); }
    }

    v[i][j] = false;
    return tmp.empty() ? curSum : *std::max_element(std::begin(tmp), std::end(tmp));
}

int  maxSum(TREASURE_MAP& m) {
    int i(0), j(0);
    getStartingPos(m, i, j);

    VISITED_MAP v(m.size(), std::vector<bool>(m.at(0).size(), false));
    return backtrack(m, v, i, j, 0);
}

int main()
{
    int H, W; std::cin >> H >> W; std::cin.ignore();
    TREASURE_MAP m(H, std::string());

    for (int i = 0; i < H; i++) { getline(std::cin, m[i]); }

    std::cout << maxSum(m) << std::endl;
}