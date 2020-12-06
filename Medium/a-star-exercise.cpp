#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <set>

using namespace std;

class Node {
public:
    int f() const { return h + g; }
    
    void set(int p_g, Node* p_from) { g = p_g; from = p_from; }
    
    void c_link(Node& p_to, int& p_cost) { links[&p_to] = p_cost; }
    
    static void createLink(Node& p_from, Node& p_to, int& p_cost) {
        p_from.c_link(p_to, p_cost); 
        p_to.c_link(p_from, p_cost); 
    }
    
    int                       id, h, g;
    Node*                     from;
    unordered_map<Node*, int> links;
};

auto cmp = [](const Node* n1, const Node* n2) { return n1->f()!=n2->f()?n1->f()<n2->f():n1->id<n2->id; };

void astar(vector<Node>& nodes, int st, int end) {
    for (Node& n : nodes) { n.g = 1e5; }
    
    set<Node*, decltype(cmp)> openset(cmp);

    nodes[st].set(0, nullptr);
    openset.insert(&nodes[st]);

    while (!openset.empty()) {
        Node* n1 = *openset.begin();
        openset.erase(n1);

        cout << n1->id << " " << n1->f() << endl;

        if ( n1->id == end ) { return; }
        for (const auto& pair : n1->links) {
            Node* n2 = pair.first;
            int   g  = n1->g + pair.second;
            if ( g < n2->g ) { n2->set(g, n1); openset.erase(n2); openset.insert(n2); }
        }
    }
}

int main() {
    int          N, E, S, G; 
    int          x, y, c;
    vector<Node> nodes(100);
    
    cin >> N >> E >> S >> G; cin.ignore();
   
    for (int i = 0; i < N && cin >> nodes[i].h;  i++) { nodes[i].id = i;                         }
    for (int i = 0; i < E && cin >> x >> y >> c; i++) { Node::createLink(nodes[x], nodes[y], c); }

    astar(nodes, S, G);
}