#include <iostream>
#include <vector>

int main()
{
    int w, h, px;
    std::cin >> w >> h;
    
    std::vector<int> bytes( w*h/8, 0); 
    for (int i = 0; i < w*h && std::cin >> px; i++)
         bytes[ i/8 ] |= (px & 1UL) << (7 - i%8);

    for ( const auto& elm : bytes ) std::cout << static_cast<char>(elm);
    std::cout << std::endl;
}