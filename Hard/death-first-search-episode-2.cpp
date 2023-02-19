#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

typedef struct {
    set<int> links;
    bool gateway; // is a gateway
    set<int> links2GW; // number of links to gateways
} Node;

pair<int, int> BFS(vector<Node>& graph, int s) // graph, skynet node id
{
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(s);
    
    visited[s] = true;
    
    int selectedNode = -1;
    
    while (not q.empty()) {
        int id = q.front();
        q.pop();
        Node n = graph[id];
        
        visited[id] = true;
        
        const auto push_neighbours = [&n, &q, &visited]() { 
            for (const int& nid : n.links) {
                if (not visited[nid]) q.push(nid);
            }
        };
        
        if (n.links2GW.size() > 1) {
            selectedNode = id;
            break;
        }
        else if (n.links2GW.size() == 1) {
            if (selectedNode == -1) {
                selectedNode = id;
                cerr << " selectedNode: " << id;
                if (id == s) break;
            }
            push_neighbours();
        }
        else if (selectedNode == -1) push_neighbours();
    
    }
    return make_pair(selectedNode, *(graph[selectedNode].links2GW.begin()));
}

int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways

    cin >> N >> L >> E; cin.ignore();
        
    vector<Node> graph(N, {set<int>(), false, set<int>()});

    for (int i = 0; i < L; i++) {
        int N1, N2; // N1 and N2 defines a link between these nodes
        cin >> N1 >> N2; cin.ignore();
        graph[N1].links.insert(N2);
        graph[N2].links.insert(N1);
    }
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        graph[EI].gateway = true;
        for (const int& nid : graph[EI].links) 
            graph[nid].links2GW.insert(EI);
    }

    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        
        pair<int, int> link = BFS(graph, SI);
        cout << link.first << ' ' << link.second << endl;
        // Cut link:
        graph[link.first].links2GW.erase(link.second);
        graph[link.first].links.erase(link.second);
        graph[link.second].links.erase(link.first);
    }
}