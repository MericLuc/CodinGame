#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    map <string, int         >  votes;
    map <int   , int         >  res = { {1, 0}, {0, 0}, {-1,0} };
    map <string, vector<int> >  tp;
    string    tmp_name, tmp_vote;
    int N, M, tmp_nbVote;  cin >> N >> M; cin.ignore();

    for (int i = 0; i < N && cin >> tmp_name >> tmp_nbVote; i++) { votes[tmp_name] = tmp_nbVote; }
    for (int i = 0; i < M && cin >> tmp_name >> tmp_vote;   i++)
        if ( votes.find(tmp_name) != votes.end() ) {
            if      ( !tmp_vote.compare("Yes") ) { tp[tmp_name].push_back(1 ); }
            else if ( !tmp_vote.compare("No")  ) { tp[tmp_name].push_back(0 ); }
            else                                 { tp[tmp_name].push_back(-1); }                            
        }
    
    for(auto& i : tp) 
        if( i.second.size() <= votes[i.first] )
            for ( auto& j : i.second ) res[j]++;
    cout << res[1] << " " << res[0] << endl;
}