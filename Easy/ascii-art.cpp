#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
    int L, H;
    string T, ROW;
    vector<string> ascii_input, ascii_output;        
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ?"; // input alphabet
    
    cin >> L >> H; cin.ignore();
    
    getline(cin, T);
    
    ascii_input  = vector<string>(H, "");
    ascii_output = vector<string>(H, "");
    
    for (int i = 0; i < H; i++) { getline(cin, ascii_input[i]); }
    
    for( auto i = 0; i < T.length(); ++i)
    {
        char s = toupper(T[i]);
        if((s < 'A') || (s > 'Z')) { s = '?'; }
        int index = alphabet.find(s);
        if (index == string::npos) { break; }
            
        for(auto i=0; i<H; i++) 
        {
          ascii_output[i] += ascii_input[i].substr(index * L, L);
        }
    }

    for (const auto& it : ascii_output ) { cout << it << endl; }
}