#include <bits/stdc++.h>

typedef std::vector<std::string> Img;
int
main()
{
    int wally_width, wally_height, pic_width, pic_height;

    std::cin >> wally_width >> wally_height; std::cin.ignore();
    Img wally(wally_height, std::string());
    for ( auto& line : wally )
        getline(std::cin, line);


    std::cin >> pic_width >> pic_height; std::cin.ignore();
    Img pic(pic_height, std::string());
    for ( auto& line : pic )
        getline(std::cin, line);

    bool match{ false };
    for (int y = 0; y <= pic_height - wally_height && !match; y++)
        for (int pic_x = 0; pic_x <= pic_width - wally_width && !match; ++pic_x)
        {
            match = true;
            for (int wally_y = 0; wally_y < wally_height && match; wally_y++)
            {
                for (int wally_x = 0; wally_x < wally_width && match; wally_x++)
                {
                    if (!isspace(wally[wally_y][wally_x]) && wally[wally_y][wally_x] != pic[y + wally_y][pic_x + wally_x])
                    {
                        match = false;
                    }
                }
            }

            if (match)
            {
                std::cout << pic_x << " " << y << "\n";
                return EXIT_SUCCESS;     
            }
        }
}