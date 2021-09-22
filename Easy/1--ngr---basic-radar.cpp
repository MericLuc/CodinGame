#include <bits/stdc++.h>

struct Record {
    std::string plate, radarName;
    long long ts;

    friend std::istream& operator>>(std::istream& is, Record& rec) { 
        return is >> rec.plate >> rec.radarName >> rec.ts; 
    }

    friend bool operator<(const Record& lhs, const Record& rhs) {
        return lhs.plate < rhs.plate;
    }
};

int main()
{
    std::map<Record, int> records;
    Record                rec;
    int                   N;

    std::cin >> N;
    for (int i = 0; i < N && std::cin >> rec; i++) {
        if ( auto it = records.find(rec); it != std::end(records) ) {
            records[rec] =  ( 3600000 * 13 ) / abs( (int)(rec.ts - it->first.ts) );
        } else { records[rec] = 0; }
    }

    for ( auto& [r, v] : records )
        if ( v > 130 ) std::cout << r.plate << " " << v << "\n";
}