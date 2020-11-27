#include <bits/stdc++.h>

using namespace std;
#define S(N) shared_ptr<N>

struct Node
{
    Node(int p_freq = 0 ) : m_freq(p_freq), m_left(nullptr), m_right(nullptr) {}

    Node(S(Node) p_left,
         S(Node) p_right) : m_freq(p_left->m_freq + p_right->m_freq), 
                            m_left(p_left), m_right(p_right) {}
    int     m_freq;
    S(Node) m_left, m_right;
};

int countRec( S(Node) cur, int symNb )
{
    int r(0);

    if ( cur ) 
    {
        if ( !(cur->m_left || cur->m_right) ) { r += cur->m_freq * symNb; }
        r += countRec(cur->m_left , symNb+1) + countRec(cur->m_right, symNb+1);
    }
    return r;
}

int main()
{
    auto cmp = [](auto p_l, auto p_r) { return p_l->m_freq > p_r->m_freq; };

    istream_iterator<int> it(cin), eos;
    vector<int>           frqs ( ++it, eos );
    priority_queue<S(Node), vector<S(Node)>, decltype(cmp) > nodes(cmp);

    for ( auto& f : frqs   ) { nodes.emplace( make_shared<Node>(f) ); }
    if  ( frqs.size() == 1 ) { cout << frqs.at(0) << endl; return 0;  }

    while ( nodes.size() > 1 )
    {
        S(Node) n1 = nodes.top(); nodes.pop();
        S(Node) n2 = nodes.top(); nodes.pop();

        nodes.emplace( make_shared<Node>(Node(n1, n2)) );
    }
    cout << countRec(nodes.top(), 0) << endl;
}