#include <iostream>
#include <string>

using namespace std;

int main()
{
    string N, s_res("Normal");
    int    s_prev(0), s_cur(0);
    int    s_rest   (-1);
    cin >> N; cin.ignore();

    for ( int i = 2; i < 10; i++ )
    {
        int l_rest = 0;
        s_cur      = 0;
        s_rest     =  (N[0] - '0') % i;

        for ( auto& c : N )
        {
            l_rest = (c - '0') % i;
            if ( s_rest != l_rest ) { s_cur++; }
            s_rest = l_rest;
        }

        if ( s_cur < s_prev ) 
        { 
            s_res = to_string(i); 
            break; 
        }
        s_prev = s_cur;
    }

    cout << s_res << endl;
}