#include <bits/stdc++.h>

typedef enum { Y08, Y17, Y27, Y56, END } VERSION;
using ALPHABET = std::array<std::string, 26>;

static const std::map<VERSION, ALPHABET> alphabets = {
    { Y08 , { "Authority", "Bills", "Capture", "Destroy", "Englishmen", "Fractious", "Galloping", "High", "Invariably", 
              "Juggling", "Knights", "Loose", "Managing", "Never", "Owners", "Play", "Queen", "Remarks", "Support", "The", 
              "Unless", "Vindictive", "When", "Xpeditiously", "Your", "Zigzag" } },
    { Y17 , { "Apples", "Butter", "Charlie", "Duff", "Edward", "Freddy", "George", "Harry", "Ink", "Johnnie", "King", 
              "London", "Monkey", "Nuts", "Orange", "Pudding", "Queenie", "Robert", "Sugar", "Tommy", "Uncle", "Vinegar", 
              "Willie", "Xerxes", "Yellow", "Zebra" } },
    { Y27 , { "Amsterdam", "Baltimore", "Casablanca", "Denmark", "Edison", "Florida", "Gallipoli", "Havana", "Italia", 
              "Jerusalem", "Kilogramme", "Liverpool", "Madagascar", "New-York", "Oslo", "Paris", "Quebec", "Roma", 
              "Santiago", "Tripoli", "Uppsala", "Valencia", "Washington", "Xanthippe", "Yokohama", "Zurich" } },
    { Y56 , { "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett", "Kilo", "Lima",
              "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", "Uniform", "Victor", "Whiskey", 
              "X-ray", "Yankee", "Zulu" } }
};

int main()
{
     std::vector< std::string > inputWords{ std::istream_iterator<std::string>(std::cin), 
                                            std::istream_iterator<std::string>() };
    VERSION                     inputVersion{ END }, targetVersion{ END };
    std::stringstream           ss;
    std::string                 translation;
    
    std::list<VERSION> cdts{ Y08, Y17, Y27, Y56 };
    for ( const auto& word : inputWords ) {        
        auto elm{ std::begin(cdts) };
        while ( elm != std::end(cdts) ) {
            if ( alphabets.at(*elm).at( word.at(0) - 'A' ) != word ) cdts.erase(elm++);
            else                                                     ++elm;
        }

        if ( 1 == std::size(cdts) ) {
            inputVersion = cdts.front();
            targetVersion = static_cast<VERSION>(( static_cast<int>(inputVersion) + 1 ) % static_cast<int>(END) );
            break;
        }
    }

    if ( END == inputVersion || END == targetVersion ) {
        std::cerr << "Unable to proceed" << std::endl;
        return EXIT_FAILURE;
    }

    std::for_each(std::cbegin(inputWords), std::cend(inputWords), [&targetVersion, &ss](const auto& word){
        ss << alphabets.at(targetVersion).at( word.at(0) - 'A') << ' ';
    } );

    translation = ss.str();
    if( translation.ends_with(' ') ) translation.pop_back();

    std::cout << translation << std::endl;

    return EXIT_SUCCESS;
}