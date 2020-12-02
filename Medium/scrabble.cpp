#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
 
using namespace std;
 
//Each letters worth in points
map<char, int> points = {
    {'a',1}, {'b',3}, {'c',3}, {'d',2},
    {'e',1}, {'f',1}, {'g',2}, {'h',4},
    {'i',1}, {'j',8}, {'k',5}, {'l',1},
    {'m',3}, {'n',1}, {'o',1}, {'p',3},
    {'q',10},{'r',1}, {'s',1}, {'t',1},
    {'u',1}, {'v',4}, {'w',4}, {'x',8},
    {'y',4}, {'z',10}
};
 
struct WORD
{
    string word;
    int score;
};
 
int computePoints(const string& word)
{
    int l_return =0;
    for(auto c : word) l_return += points[c];
    return l_return;
}
 
bool compareStrings(const string& lhs, const string& rhs)
{
    int count = 0;
    string tmp = rhs;
   
    for(auto l: lhs)
    {
        int current_r = 0;
        for(auto r: tmp)
        {
            if(l == r){ count++; tmp.erase(current_r, 1); break; }
            current_r++;
        }

        if(count == rhs.length()) return true;
    }
   
    return false;
}
 
int main()
{
    int N;
    WORD current_word;
    cin >> N; cin.ignore();
   
    vector<WORD> dictionary;
   
    for (int i = 0; i < N; i++) 
    {
        string W;
        getline(cin, W);
        if(W.length() <= 7)
        {
            current_word.word = W;
            current_word.score = computePoints(W);
            dictionary.push_back(current_word);
        }
    }
    string LETTERS;
    getline(cin, LETTERS);
   
    if(LETTERS.length() > 0)
    {
        int maximum = -1, index = 0;
        string tempWord = "";
        int tempVal = 0;
        for(int i =0; i < dictionary.size(); ++i)
        {
            tempWord = dictionary[i].word;
            tempVal = dictionary[i].score;
       
            if( compareStrings(LETTERS, tempWord) )
            {
                if(tempVal > maximum)
                {
                    maximum = tempVal;
                    index = i;
                }
            }
        }
        cout << dictionary[index].word << endl;
    }
}