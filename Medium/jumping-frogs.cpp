#include <bits/stdc++.h>

struct Frog {
    int x, y, k;
    friend auto& operator>>(std::istream& is, Frog& f) { return is >> f.x >> f.y >> f.k; }
};

int main() {
    std::istream_iterator<Frog> is(std::cin), eos;
    std::vector<Frog>           f(is, eos);

    bool ret{ true };
    for (int i = 0; i < std::size(f); ++i) {
        int j{ (i + 1) % 3 };
        ret &= (abs(f[j].x - f[i].x) % std::__gcd(f[i].k, f[j].k) == 0);
        ret &= (abs(f[j].y - f[i].y) % std::__gcd(f[i].k, f[j].k) == 0);
    }
    std::cout << ( ret ? "Possible\n" : "Impossible\n" );
}