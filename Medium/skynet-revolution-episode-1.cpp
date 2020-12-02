#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    struct networkPoint
    {
        int         index;
        vector<int> neighbours;
        bool        isGateway;
    };
    
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
    
    vector<networkPoint>    network(N);         // Network
    string                  l_return;        // Output decision
    
    // Initialize the network
    for (int i = 0; i < N; i++) 
    {
        networkPoint l_currentNode;
        l_currentNode.index      = i;
        l_currentNode.neighbours = vector<int>();
        l_currentNode.isGateway  = false;
        
         network[i] = l_currentNode;
    }
    
    // Fills the connections
    for (int i = 0; i < L; i++) 
    {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();

        network[N1].neighbours.push_back(N2);
        network[N2].neighbours.push_back(N1);
    }
    
    for (int i = 0; i < E; i++) 
    {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        
        network[EI].isGateway = true;
    }

    // game loop
    while (1) 
    {
        l_return = "";
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        
        // Go through all the neighbours
        for( auto it = network[SI].neighbours.begin(); it != network[SI].neighbours.end(); it++ )
        {
            if( network[*it].isGateway )
            {
                l_return = to_string(SI) + " " + to_string(*it);
                break;
            }
        }
        
        if( l_return.empty() )
        {
            for( auto it = network[SI].neighbours.begin(); it != network[SI].neighbours.end(); it++ )
            {
                for( auto it2 = network[*it].neighbours.begin(); it2 != network[*it].neighbours.end(); it2++ )
                {
                    if( network[*it2].isGateway )
                    {
                        l_return = to_string(*it) + " " + to_string(*it2);
                        break;
                    }
                }
            }
        }

        // Example: 0 1 are the indices of the nodes you wish to sever the link between
        cout << l_return << endl;
    }
}