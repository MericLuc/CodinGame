#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// OK
void m_U(int& p_y, 
         int& p_min_y,
         int& p_max_y)
{
    int tmp_y;
    
    p_max_y = p_y < p_max_y ? p_y-1: p_max_y;
    tmp_y = p_max_y - (p_max_y - p_min_y)/2;
    
    p_y = (tmp_y == p_y) ? tmp_y -1 : tmp_y;
}

// OK
void m_D(int& p_y, 
         int& p_min_y,
         int& p_max_y)
{
    int tmp_y;
    
    p_min_y = p_y > p_min_y ? p_y+1: p_min_y;
    tmp_y = p_min_y + (p_max_y - p_min_y)/2;
    
    p_y = (tmp_y == p_y) ? tmp_y +1 : tmp_y;
}

// OK
void m_R(int& p_x, 
         int& p_min_x,
         int& p_max_x)
{
    int tmp_x;
    
    p_min_x = p_x > p_min_x ? p_x+1 : p_min_x;
    tmp_x = p_min_x + (p_max_x - p_min_x)/2;
    
    p_x = (tmp_x == p_x) ? tmp_x +1 : tmp_x; 
}

//
void m_L(int& p_x, 
         int& p_min_x,
         int& p_max_x)
{
    int tmp_x;
    
    p_max_x = p_x < p_max_x ? p_x-1 : p_max_x;
    tmp_x = p_max_x - (p_max_x - p_min_x)/2;
    
    p_x = (tmp_x == p_x) ? tmp_x -1 : tmp_x;
}
         
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int W, H;                                       // Dimensions of the building.
    cin >> W >> H; cin.ignore();
    
    int N;                                          // maximum number of turns before game over.
    cin >> N; cin.ignore();
    
    int X0, Y0;                                     // Initial position
    int tmp_x, tmp_y;                               // temporaries
    int min_x(0), max_x(W-1), min_y(0), max_y(H-1); // possible boundaries
    cin >> X0 >> Y0; cin.ignore();

    while (1) {
        string bombDir;
        cin >> bombDir; cin.ignore();

            if(bombDir == "U")
            {
                m_U(Y0, min_y, max_y);
            }
            else if(bombDir == "UR")
            {
                m_U(Y0, min_y, max_y);
                m_R(X0, min_x, max_x);
            }
            else if(bombDir == "R")
            {
                m_R(X0, min_x, max_x);
            }
            else if(bombDir == "DR")
            {
                m_D(Y0, min_y, max_y);
                m_R(X0, min_x, max_x);
            }
            else if(bombDir == "D")
            {
                m_D(Y0, min_y, max_y);
            }
            else if(bombDir == "DL")
            {
                m_D(Y0, min_y, max_y);
                m_L(X0, min_x, max_x);
            }
            else if(bombDir == "L")
            {
                m_L(X0, min_x, max_x);
            }
            else if(bombDir == "UL")
            {
                m_U(Y0, min_y, max_y);
                m_L(X0, min_x, max_x);
            }

        cout << X0 << " " << Y0 << endl;
    }
}