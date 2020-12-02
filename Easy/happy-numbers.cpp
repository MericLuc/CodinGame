#include <iostream>
#include <string>
#include <set>

using namespace std;

void test_happy(string& p_in)
{
    string      l_tmp = p_in;
    set<string> l_mem;
    
    while(l_mem.find(l_tmp) == l_mem.end() )
    {
        l_mem.insert(l_tmp);
        int         l_buffer = 0;
        
        for(auto& c: l_tmp) { l_buffer += (c - '0') * (c - '0');     }
        if (l_buffer == 1 ) { cout << p_in << " :)" << endl; return; }
        
        l_tmp = to_string(l_buffer);
    }
    cout << p_in << " :(" << endl;
}
                
main()
{
    int            N;
    string         curr_entry; 
    
    cin >> N; cin.ignore();
    
    for (int i = 0; i < N; i++) 
    { 
        getline(cin, curr_entry);
        test_happy(curr_entry);
    }
}