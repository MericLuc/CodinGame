#include <bits/stdc++.h>

uint32_t* v;

inline uint32_t cycleLength(const uint32_t& i) {
	if ( v[i] ) return( v[i] );
	v[i]= 1 + cycleLength( (i&1) ? (3*i+1) : i/2 );
	return( v[i] );
}

struct Range { 
    uint32_t A, B;
    friend std::istream& operator>>(std::istream& is, Range& r) { return is >> r.A >> r.B; }
};

int main()
{  
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::istream_iterator<Range> it(std::cin), eos;
    std::vector<Range> ranges(it, eos);

    
    v = (uint32_t*)malloc(1570824737*sizeof(uint32_t));
    for(uint32_t i=0;i<30;++i)v[1UL<<i]=i+1;

    for ( auto& r : ranges ) {
        uint32_t best{0}, longest{0};
        for ( uint32_t i = r.A; i <= r.B; ++i )
            if ( auto cur = cycleLength(i); cur > longest ) { longest = cur; best = i; }

        std::cout << best << " " << longest << "\n";
    }
}