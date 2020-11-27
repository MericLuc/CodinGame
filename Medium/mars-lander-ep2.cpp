#include <iostream>

int main()
{
    int nbPts ;  /*!< Number of landing points      */
    int x , y ;  /*!< Position components           */
    int X , Y ;  /*!< Landing coordinates           */
    int vx, vy;  /*!< Speed components              */
    int fuel  ;  /*!< Remaining fuel level          */ 
    int power ;  /*!< Power of the rockets          */
    int rotate;  /*!< Rotation angle of Mars Lander */

    // -- Compute the landing position -- //
    int l_lastX, l_lastY;
    std::cin >> nbPts;
    while ( nbPts-- )
    {
        std::cin >> x >> y;

        if ( y == l_lastY ) 
        {
            X = ( l_lastX + x )/2; 
            Y = l_lastY;
        }
        l_lastX = x; 
        l_lastY = y;
    }

    // -- Play the game -- //
    while(1)
    {
        std::cin >> x >> y >> vx >> vy >> fuel >> rotate >> power;

        rotate = ( (y - Y) > 100 ) ? ( ((x - X) / 100) + vx * 0.64 ) : 0;
        power  = ( (vy < -20) || (vx*vx > 1600) ) ? 4 : 2;

        std::cout << rotate << " " << power << std::endl;
    }
}