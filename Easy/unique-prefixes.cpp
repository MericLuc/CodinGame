#include <bits/stdc++.h>

using namespace std;

class Trie {
    public:
        static const int   MAX_SONS = 123;
        static set<string> st_words;
        unique_ptr<Trie>   m_sons[MAX_SONS];
        int                m_freq;

        Trie(): m_freq(0) { 
            for ( int i = 0; i < MAX_SONS; i++ ) { m_sons[i] = nullptr; }
        }

        void insert( const string& p_str ) {
            if ( st_words.count( p_str ) ) { return; }
            st_words.insert( p_str );
            Trie* cur(this);
            for ( const auto& c : p_str ) {
                if (!cur->m_sons[c]) { cur->m_sons[c] = make_unique<Trie>(Trie()); }
                cur =cur->m_sons[c].get();
                ++cur->m_freq;
            }
        }

        string prefix( const string& p_str ) const {
            const Trie* cur(this);
            string l_res("");
            for ( const auto& c : p_str ) {
                l_res += c;
                if (  cur->m_sons[c]->m_freq == 1 ) { return l_res; }
                cur = cur->m_sons[c].get();
            }
            return l_res;
        }
};

set<string> Trie::st_words;

int main() {
    istream_iterator<string> it(cin), eos;
    vector<string>           v (++it, eos);
    unique_ptr<Trie>         root(new Trie());
    
    for ( auto& wrd : v ) { root->insert( wrd );                 }
    for ( auto& wrd : v ) { cout << root->prefix( wrd ) << endl; }
}