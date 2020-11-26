#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
#include <stack>
#include <map>
#include <utility>

using namespace std;

#define D(v, it) distance(v.begin(), it)

#define ERR_OOB  "POINTER OUT OF BOUNDS"
#define ERR_SYN  "SYNTAX ERROR"
#define ERR_INC  "INCORRECT VALUE"

bool syntaxCheck( const string& str, map<int,int>& corresp )
{
    stack< pair<char, int> >  S;
    for(int i = 0; i < str.length(); ++i )
    {
        switch ( str[i] )
        {
            case '[': 
                S.push( make_pair(str[i],i) ); 
            break;
            case ']': 
                if ( S.empty() || S.top().first != '[' ) { return false; }
                corresp[S.top().second] = i;
                corresp[i             ] = S.top().second;
                S.pop();
            break;
            default : break;
        }
    }
    return S.empty() ;
}

int main()
{
    string prog, r, out;
    int    L, S, N, in;
    cin >> L >> S >> N; cin.ignore();

   
    map<int, int> m;                 // Mapping of brackets
    vector<uint8_t>  mem(S,0);       // Memory array
    auto it = mem.begin();           // Memory pointer
    queue<int> cmds;                 // List of inputs

    // Lines of the program
    for (int i = 0; i < L && getline(cin, r); i++) { prog += r;      }

    // Inputs to the program
    for (int i = 0; i < N && cin >> in      ; i++) { cmds.push(in);  }

    if ( !syntaxCheck( prog, m ) ) { cout << ERR_SYN << endl; return -3; }

    for ( auto& [i,j] : m ) { cerr << i << " : " << j << endl; }

    cerr << "Array size : "     << S << " bytes "            << endl;
    cerr << "--- program --- (" << L << " lines )\n" << prog << endl;
    cerr << "--- inputs  --- (" << N << " inputs)\n"         << endl; 

    auto c = prog.begin();
    while ( c != prog.end() )
    {
        switch ( *c )
        {
            case '>' : 
                if ( D(mem, it) < S - 1 ) { ++it;                       } 
                else                      { cout << ERR_OOB; return -1; } 
            break;
            case '<' : 
                if ( D(mem, it)         ) { --it;                       }
                else                      { cout << ERR_OOB; return -1; }
            break;
            case '+' : 
                if ( *it < 0xff         ) { ++*it;                      } 
                else                      { cout << ERR_INC; return -2; }
            break;
            case '-' :
                if ( *it > 0            ) { --*it;                      } 
                else                      { cout << ERR_INC; return -2; }
            break;
            case '.' : 
                out += (char)*it;
            break;
            case ',' : 
                if ( !cmds.empty() ) { *it = cmds.front(); cmds.pop(); } 
            break;
            case '[' : 
                if ( !*it ) { c = prog.begin() + m[D(prog, c)]; }
            break;
            case ']' : 
                if ( *it  ) { c = prog.begin() + m[D(prog, c)]; } 
            break; 
            default  : break;
        }

        c++;
    }

    cout << out;
}