#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Node {
    map<int, Node*> children;
};

Node* head;
int cmpt = 0;

void addTel(string telephone)
{
    auto node = head;
    for(auto i = 0; i < telephone.size(); ++i)
    {
        int number = telephone.at(i) + '0'; 
        auto it = node->children.find(number);
        
        if(it == node->children.end())
        {
            node->children[number] = new Node{};
            cmpt++;
        }
        node = node->children[number];
    }
}

int main()
{
    int N;
    cin >> N; cin.ignore();
    head = new Node{};
    
    for (int i = 0; i < N; i++) 
    {
        string telephone;
        cin >> telephone; cin.ignore();
        addTel(telephone);
    }

    cout << cmpt << endl;
}