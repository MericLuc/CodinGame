#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class State
{
    public:
        State(char p_name = ' '): m_name(p_name), m_links(map<char, State*>()) {}

        void addLink(char p_key, State* p_state) { m_links[p_key] = p_state; }
        char name   (void) const                 { return m_name; }

        State* nextState(char p_key) const {
            return m_links.find(p_key) == m_links.end() ? nullptr : m_links.at(p_key);
        }

        bool operator==(const State& p_other) { return m_name == p_other.name(); }
    private:
        char              m_name;
        map<char, State*> m_links;
};

int main()
{
    map<char, State> states;
    string           alphaStr, statesStr, strStateStr, 
                     endStateStr, transStr, wordStr;
    int              nbTrans , nbWords  ;

    getline(cin, alphaStr );
    getline(cin, statesStr);

    for ( auto& c : statesStr ) if ( c != ' ' ) { states[c] = State(c); }

    cin >> nbTrans; cin.ignore();
    for (int i = 0; i < nbTrans && getline(cin, transStr); i++) 
    {
        char c1(transStr[0]), c2(transStr[4]), link(transStr[2]);
        if ( states.find(c1) != states.end() && 
             states.find(c2) != states.end() )
        {
            states[c1].addLink(link, &states[c2] );
        }
    }

    getline(cin, strStateStr);
    getline(cin, endStateStr);

    cin >> nbWords; cin.ignore();
    for (int i = 0; i < nbWords && getline(cin, wordStr); i++) 
    {
        bool   isOk(true);
        State* curState = &states[strStateStr[0]];

        for ( auto& c : wordStr ) 
        {
            curState = curState->nextState(c);
            if ( !curState ) { isOk = false; break; }
        }
         cout << ( isOk && (endStateStr.find(curState->name()) != string::npos) ? "true" : "false" ) << endl;
    }
}