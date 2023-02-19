#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define EXIT -1

struct Room {
    int id, money, top, right;
};

static vector<Room> rooms;
static vector<int>  results_memoized;

int DFS(int index)
{
    if (results_memoized[index] != -1)
        return results_memoized[index];
    
    Room& c     { rooms[index] };
    int   result{ c.money };
    
    if (c.top != EXIT && c.right != EXIT) {
        result = c.money + max(DFS(c.top), DFS(c.right));
    }
    else {
        if      (c.top   != EXIT) { result = c.money + DFS(c.top);   }
        else if (c.right != EXIT) { result = c.money + DFS(c.right); }
    }

    results_memoized[index] = result;
    return result;
}

int main()
{
    int N;
    cin >> N; cin.ignore();
    
    rooms            = vector<Room>(N, {-1, 0, EXIT, EXIT });
    results_memoized = vector<int> (N, -1);

    for (int i = 0; i < N; ++i) {
        string edgeT, edgeR;
        Room& r = rooms[i];
        cin >> r.id >> r.money >> edgeT >> edgeR;
        
        if (edgeT != "E") r.top = stoi(edgeT);
        if (edgeR != "E") r.right = stoi(edgeR);
    }
        
    cout << DFS(0) << endl;
}