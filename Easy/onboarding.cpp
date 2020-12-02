#include <iostream>
#include <string>

int main()
{
    while (1) 
    {
        std::string e1, e2;
        int         d1, d2;

        std::cin >> e1 >> d1 >> e2 >> d2; std::cin.ignore();
        std::cout << ( (d1 < d2) ? e1 : e2 ) << std::endl;
    }
}