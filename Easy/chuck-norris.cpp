#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string unary(char p_val, int p_number) {
    string l_return = "";
    
    if( p_number <= 0 ) { return l_return; }
    
    l_return += (p_val == '1') ? "0 " : "00 ";
    
    for(auto i = 0; i < p_number; ++i) { l_return += "0"; }
    l_return += " ";

    return l_return;
}

int main() {
    string MESSAGE, bin_message, response;
    getline(cin, MESSAGE);

  
    if(!MESSAGE.empty())
    {
        char l_current;
        for(auto i = 0; i < MESSAGE.length(); ++i)
        {
            l_current = MESSAGE[i];
            for(auto bits = 6; bits >= 0; bits--)
                bin_message += ( (l_current >> bits) & 1UL ) ? "1" : "0";
        }
                
        int l_index(0), l_consec(0);
        char l_currentValue;
        while( l_index < bin_message.length() )
        {
            l_currentValue = bin_message[l_index];
            
            for( auto i = l_index; i < bin_message.length(); ++i )
            {
                if( bin_message[i] == l_currentValue ) { ++l_consec; }
                else { break; }
            }
            
            response += unary(l_currentValue, l_consec);
            l_index  += l_consec;
            l_consec  = 0;
        }
    }
    response = response.substr(0, response.size()-1);
    cout << response << endl;
}