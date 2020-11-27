#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Node
{
    public:
        Node(char p_name): m_name(p_name), m_sons(vector<Node*>()) {}
        ~Node(){}

    public:
        void addSon(Node* p_son) { 
            if ( std::find_if(m_sons.begin(), 
                              m_sons.end  (), 
                              [p_son](Node* n) {
                                   return n->getName() == p_son->getName(); 
                                   }
                             )
                              == m_sons.end() ) { m_sons.push_back(p_son); }
        }
        const vector<Node*>& getSons(void) const { return m_sons; }
        char getName(void) const { return m_name; }

        bool isRedundant(set<char>& checked, 
                         Node*      p_node = nullptr) {
            if      ( p_node == nullptr ) { p_node = this; }
            else if ( p_node == this    ) { return true;   }

            for ( auto it : m_sons ) 
            { 
                if ( checked.count(it->getName()) == 0 ) 
                {
                    checked.insert(it->getName());

                    if ( it->getName() == p_node->getName() ||
                         it->isRedundant(checked, p_node) ) { return true; }
                }
            }
            return false;
        }

        bool operator==(char p_other       ) { return m_name == p_other;        }
        bool operator==(const Node& p_other) { return m_name == p_other.m_name; }

        friend ostream& operator<<(ostream& os, const Node& n);

    private:
        char          m_name;
        vector<Node*> m_sons;
};

ostream& operator<<(ostream& os, const Node& n) {
    os << n.m_name << " (" << n.m_sons.size() << " sons)";
    return os;
}

int main() {
    vector<Node*> ineqGraph;
    string        ineqStr  ;
    int           ineqCount;

    cin >> ineqCount; cin.ignore();

    while ( ineqCount-- && getline(cin, ineqStr) ) 
    {
        cerr << ineqStr[0] << " > " << ineqStr[4] << endl;
        char c1(ineqStr[0]), c2(ineqStr[4]);

        Node* n1(nullptr);
        Node* n2(nullptr);

        auto l_n1 =  std::find_if(ineqGraph.begin(), 
                                  ineqGraph.end  (), 
                                  [c1](Node* n) { return n->getName() == c1; });

        if ( l_n1 == ineqGraph.end() )
        {
            ineqGraph.push_back( new Node(c1) );
        }

        for ( int i = 0; i < ineqGraph.size(); i++ )
        {
            if ( ineqGraph[i]->getName() == c1 ) { n1 = ineqGraph[i]; break; }
        }

        auto l_n2 =  std::find_if(ineqGraph.begin(), 
                                  ineqGraph.end  (), 
                                  [c2](Node* n) { return n->getName() == c2; });

        if ( l_n2 == ineqGraph.end() )
        {
            ineqGraph.push_back( new Node(c2) );
        }

        for ( int i = 0; i < ineqGraph.size(); i++ )
        {
            if ( ineqGraph[i]->getName() == c2 ) { n2 = ineqGraph[i]; break; }
        }

        n1->addSon(n2);
    }

    bool consistent(true);
    for ( auto& it : ineqGraph ) 
    { 
        set<char> curSet;
        if ( it->isRedundant(curSet) ) { consistent = false; break; }
    }

    cout << ( consistent ? "consistent" : "contradiction" ) << endl;
}