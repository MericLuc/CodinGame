#include <bits/stdc++.h>

struct Planet {
    std::string name;
    double      radius, mass, dist, density;

    friend std::istream& operator>>(std::istream& ss, Planet& pl) {
        std::string rad, mass, dist;
        ss >> pl.name >> rad >> mass >> dist; ss.ignore();
        pl.radius  = atof(rad .c_str());
        pl.mass    = atof(mass.c_str());
        pl.dist    = atof(dist.c_str());
        pl.density = pl.mass / ( 4*M_PI*pow(pl.radius, 3)/3 );
        return ss;
    }

    friend bool operator<(const Planet& p1, const Planet& p2) { return p1.dist < p2.dist; }
};

int main()
{
    int N;
    std::cin >> N; std::cin.ignore();

    std::vector<Planet> planets(N);
    for ( auto& planet : planets ) std::cin  >> planet;

    std::sort( std::begin(planets), std::end(planets) );
    std::cout << (std::find_if( std::begin(planets), std::end(planets), 
    [a = planets.front()](const auto& p){ 
        return a.radius * pow(2 * a.density/p.density, 1/3.0) < p.dist; } ))->name << "\n";
}