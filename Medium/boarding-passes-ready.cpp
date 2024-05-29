#include <bits/stdc++.h>

struct Passenger  {
    static const size_t LIMIT_NAME_SIZE = 100;

    int         row{ 1 };
    char        seat{ 'A' };
    std::string name;

    Passenger() noexcept {}
    Passenger(std::string input) {
        auto idx{ input.find_first_of(',') };
        if ( idx == std::string::npos )
            throw std::invalid_argument( "Unable to parse passenger from : " + input );
    
        name = input.substr(0,idx);
        if ( 2 != std::sscanf(input.substr(idx + 1).c_str(), "%d%c", &row, &seat) )
            throw std::invalid_argument( "Unable to parse passenger from : " + input.substr(idx+1) );
    }

    friend bool operator<(const Passenger& lhs, const Passenger& rhs) noexcept {
        return lhs.seat < rhs.seat;
    }
};

struct Plane {
    int widthCapacity{ -1 }, heightCapacity{ -1 };

    typedef enum { LEFT, RIGHT } SIDE;

    Plane() { 
        std::cin >> heightCapacity; std::cin.ignore();
        std::cin >> widthCapacity;  std::cin.ignore();

        if ( (0 != (widthCapacity % 2))                      || 
             ((1 > heightCapacity) || (20 < heightCapacity)) || 
             ((2 > widthCapacity)  || (8  < widthCapacity )) )
            throw std::logic_error( "Unable to parse plane dimensions" );
    }

    SIDE getSide(const Passenger& p) const noexcept {
        return (p.seat <  (char)('A' + widthCapacity/2)) ? LEFT : RIGHT;
    }
};

int main() {
    std::string       input;
    Plane             plane;
    int               n;
    std::stringstream ss;
    std::vector<std::deque<Passenger>> boardingQueue(plane.heightCapacity + 1, std::deque<Passenger>{});

    std::cin >> n; std::cin.ignore();
    while (getline(std::cin, input) ) { 
        Passenger p{input};
        boardingQueue[p.row].push_back(p);
    }

    for ( auto& p : boardingQueue ) 
        std::sort(std::begin(p), std::end(p));
    
    Plane::SIDE curSide{ Plane::SIDE::LEFT };
    while ( n ) {
        for ( int i{ plane.heightCapacity }; i >= 0; i-- ) {
            if ( std::empty(boardingQueue[i]) )
                    continue;
            if ( Plane::SIDE::LEFT == curSide ) {
                if ( auto& candidate{ boardingQueue[i].front() }; curSide == plane.getSide(candidate) ) {
                    ss << candidate.name << ',';
                    boardingQueue[i].pop_front();
                    --n;
                }
            } else {
                if ( auto& candidate{ boardingQueue[i].back() }; curSide == plane.getSide(candidate) ) {
                    ss << candidate.name << ',';
                    boardingQueue[i].pop_back();
                    --n;
                }
            }
        }
        
        std::string output{ ss.str() };
        if ( output.ends_with(',')) {
            output.pop_back();
            std::cout << "Now boarding: " << output << std::endl;
            ss.str("");
        }
        curSide = (Plane::SIDE::LEFT == curSide) ? Plane::SIDE::RIGHT : Plane::SIDE::LEFT;
    }
}