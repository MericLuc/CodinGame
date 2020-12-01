#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h>

using namespace std;

#define ID   0
#define NAME 1
#define ADDR 2
#define TEL  3
#define LONG 4
#define LATI 5
#define OK   6

int main()
{
    double cLon, cLat, d_x, d_y, d(1e9);
    char   del = ';';
    int    l_index = 0;
    
    string LON, LAT, DEFIB;
    cin >> LON >> LAT; cin.ignore();
    
    replace(LON.begin(), LON.end(), ',', '.');
    replace(LAT.begin(), LAT.end(), ',', '.');
    cLon = (M_PI / 180) * stod(LON); 
    cLat = (M_PI / 180) * stod(LAT);
        
    int N; cin >> N; cin.ignore();
    vector< vector<string> > elements(N, vector<string>(OK, ""));
    for (int i = 0; i < N; i++) 
    {
        int j = 0;
        getline(cin, DEFIB);
        
        std::stringstream ss(DEFIB);
        string l_tmp;
        while( getline(ss, l_tmp, del) ) { elements[i][j++] = l_tmp; }
    }

    int tmp = 0;
    for( auto& it : elements )
    {
        double tmpLon, tmpLat, tmpRes;
        replace(it[LONG].begin(), it[LONG].end(), ',', '.');
        replace(it[LATI].begin(), it[LATI].end(), ',', '.');
        tmpLon = (M_PI / 180) * stod(it[LONG]); 
        tmpLat = (M_PI / 180) * stod(it[LATI]);
        
        d_x = (cLon - tmpLon) * cos( (cLat + tmpLat) / 2 );
        d_y = cLat - tmpLat;
        tmpRes = sqrt( d_x*d_x + d_y*d_y ) * 6371;
                
        if(tmpRes < d)
        {
            d = tmpRes;
            l_index = tmp;
        }
        
        tmp++;
    }

    cout << elements[l_index][NAME] << endl;
}