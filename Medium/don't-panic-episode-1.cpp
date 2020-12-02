#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main()
{
    int nbFloors;              // number of floors
    int width;                 // width of the area
    int nbRounds;              // maximum number of rounds
    int exitFloor;             // floor on which the exit is found
    int exitPos;               // position of the exit on its floor
    int nbTotalClones;         // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators;           // number of elevators
    cin >> nbFloors >> width >> nbRounds >> exitFloor 
        >> exitPos >> nbTotalClones >> nbAdditionalElevators 
        >> nbElevators; cin.ignore();
        
    string l_return;
    map< int, vector<int> > l_elevatorMap;
        
    for (int i = 0; i < nbElevators; i++) 
    {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos;   // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        
        l_elevatorMap[elevatorFloor].push_back(elevatorPos);
    }

    // game loop
    while (1) {
        l_return = "WAIT";
        int cloneFloor;   // floor of the leading clone
        int clonePos;     // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();
        
        // cerr << "current Floor: " << cloneFloor << " and pos: " << clonePos << endl;
        
        if( cloneFloor < 0 || clonePos < 0)
        {
            // DUMMY
        }
        else if( cloneFloor < exitFloor )
        {
            int pos_elevator = l_elevatorMap[cloneFloor][0];
            
            if( (pos_elevator < clonePos && direction == "RIGHT") ||
                (pos_elevator > clonePos && direction == "LEFT") )
            {
                l_return = "BLOCK";
            }
        }
        else
        {
            if( (exitPos < clonePos && direction == "RIGHT") ||
                (exitPos > clonePos && direction == "LEFT") )
            {
                l_return = "BLOCK";
            }
        }

        cout << l_return << endl; // action: WAIT or BLOCK
    }
}