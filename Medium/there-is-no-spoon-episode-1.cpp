#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/
int main()
{
    int width;       // the number of cells on the X axis
    int height;      // the number of cells on the Y axis
    string l_return; // output
    map<int, vector<int> > nodesMap;

    cin >> width; cin.ignore(); cin >> height; cin.ignore();
    
    for (int i = 0; i < height; i++) 
    {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        
        int l_cmpt = 0;
        for(string::iterator it = line.begin();  it != line.end(); ++it)
        {
            if( *it == '0' ) nodesMap[i].push_back(l_cmpt);
            ++l_cmpt;
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        if( nodesMap.find(i) != nodesMap.end() )
        {
            for( int j = 0; j < nodesMap[i].size(); j++)
            {
                int l_current = nodesMap[i][j];
                
                l_return = to_string(l_current) + " " + to_string(i);
                  
                  if (j == nodesMap[i].size() -1) l_return += " -1 -1";
                  else                            l_return += " " + to_string( nodesMap[i][j+1]) + " " + to_string(i);
    
                bool l_found = false;
                for( int k = i +1; k < height; ++k)
                {
                    if( nodesMap.find(k) != nodesMap.end() )
                    {
                        if( find(nodesMap[k].begin(), nodesMap[k].end(), l_current) != nodesMap[k].end() )
                        {
                            l_return += " " + to_string(l_current) + " " + to_string(k);
                            l_found = true;
                            break;
                        }
                    }
                }
                
                if(!l_found)
                {
                    l_return += " -1 -1";
                }
                
                cout << l_return << endl;
            }
        }
    }
}