#include <iostream>
#include <string>
#include <map>
#include <climits>

using namespace std;

static const map<char, int> DIRS_R = {
    { '^', -1 },
    { 'v',  1 },
    { '<',  0 },
    { '>',  0 }
};

static const map<char, int> DIRS_C = {
    { '^',  0 },
    { 'v',  0 },
    { '<', -1 },
    { '>',  1 }
};

int main() 
{
    int    W,   H,   st_r,   st_c,   N;
    cin >> W >> H >> st_r >> st_c >> N; cin.ignore();

    int minPath(INT_MAX), minIdx(-1);
    for ( int i = 0; i < N; ++i ) 
    {
        char curMap[20][20];
        for (int i_r = 0; i_r < H; ++i_r) 
        {
            string curRow;
            getline(cin, curRow);
            for (int i_c = 0; i_c < W; ++i_c) 
            {
                curMap[i_r][i_c] = curRow[i_c];
            }
        }

        int i_r_2(st_r), i_c_2(st_c), pL(0);
        while(pL >= 0 ) 
        {
            ++pL;
            char& currentCell = curMap[i_r_2][i_c_2];
            if ('T' == currentCell) { break; }       
            
            i_r_2 += DIRS_R.at(currentCell);
            i_c_2 += DIRS_C.at(currentCell);

            if (i_r_2 < 0                   || 
                i_r_2 >= H                  || 
                i_c_2 < 0                   || 
                i_c_2 >= W                  ||
                curMap[i_r_2][i_c_2] == '.' || 
                curMap[i_r_2][i_c_2] == '#' ) 
            {
                pL = -1;
            }
            currentCell = '.';
        }

        if (pL >= 0 && pL < minPath) 
        {
            minPath = pL;
            minIdx = i;
        }
    }
    
    cout << ( ( minIdx >= 0 ) ? to_string(minIdx) : "TRAP" )<< endl;
}