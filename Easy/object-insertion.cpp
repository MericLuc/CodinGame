#include <bits/stdc++.h>

using GridType = std::vector< std::string >;

auto loadArray = [](){
    int rows, cols;
    std::cin >> rows >> cols; std::cin.ignore();
    GridType ret(rows, "");
    for ( auto& row : ret ) std::getline( std::cin, row );

    return ret;
};

auto printArray = [](const GridType& array, std::ostream& os, auto... args) {
    if( sizeof...(args) ) ((os << args << "\n"), ...);
    std::for_each(std::begin(array), std::end(array), 
        [&os](const auto& line){ os << line << "\n"; });
};

auto testObjectAtPos = [](const GridType& obj, const GridType& grid, int row, int col) {
    for ( int di = 0; di < std::size(obj); ++di )
        for ( int dj = 0; dj < std::size(obj[0]); ++dj )
            if ( grid[row + di][col + dj] != '.' && obj[di][dj] != '.' )
                return false;
    return true;
};

auto placeObjectAtPos = [](const GridType& obj, const GridType& grid, int row, int col) {
    auto ret{ grid };
    for ( int di = 0; di < std::size(obj); ++di )
        for ( int dj = 0; dj < std::size(obj[0]); ++dj )
            if ( obj[di][dj] != '.' ) ret[row + di][col + dj] = obj[di][dj];
    return ret;
};

int main()
{
    auto object = loadArray();
    auto grid   = loadArray();

    printArray(object, std::cerr, "---------", "The object", "---------");
    printArray(grid  , std::cerr, "---------", "The grid"  , "---------");

    std::vector< std::pair<int, int> > positions{};

    for ( auto i = 0; i < std::size(grid   ) - std::size(object   ) + 1; i++ )
        for ( auto j = 0; j < std::size(grid[0]) - std::size(object[0]) + 1; ++j )
            if ( testObjectAtPos(object, grid, i, j) )
                positions.emplace_back( i, j );

    std::cout << std::size(positions) << "\n";
    if ( std::size(positions) == 1 )
        printArray( placeObjectAtPos(object, grid, positions[0].first, positions[0].second), std::cout );
}
