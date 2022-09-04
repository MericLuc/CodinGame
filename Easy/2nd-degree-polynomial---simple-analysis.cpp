#include <bits/stdc++.h>

struct Pt {
    double x, y;
    friend bool operator<(const Pt& lhs, const Pt& rhs) { return lhs.x < rhs.x; }
    friend std::ostream& operator<<(std::ostream& o, const Pt& pt) { 
        return o << std::setprecision(3) << "(" << pt.x << "," << pt.y << ")"; 
    }
};

int main()
{
    float        a, b, c;
    std::set<Pt> res;
    std::cin >> a >> b >> c; std::cin.ignore();
    
    res.insert({0, c});
    if         ( 0.f == a ) {
        if     ( 0.f == b ) { res.insert({0   , c}); } 
        else                { res.insert({-c/b, 0}); }
    } else {
        double delta = b*b - 4*a*c, 
               x1    = (-b - sqrt(delta)) / (2 * a), 
               x2    = (-b + sqrt(delta)) / (2 * a);
        if ( 0 <= delta ) {
            res.insert({ x1, a*x1*x1 + b*x1 + c});
            res.insert({ x2, a*x2*x2 + b*x2 + c});
        }
    }

    std::stringstream ss;
    std::string       out;
    for ( const auto& pt : res )
        ss << pt << ",";
    out = ss.str();
    out.pop_back();
    std::cout << out << '\n';
}