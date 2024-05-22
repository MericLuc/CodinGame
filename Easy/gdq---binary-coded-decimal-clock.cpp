#include <bits/stdc++.h>

#define OUT(val, shift) ( ((val >> shift) & 1U) ? "#####" : "_____" )
#define REQUIRED_SIZE 10

int main() {

    std::string in;
    getline(std::cin, in);

    if ( REQUIRED_SIZE != std::size(in) )
        return EXIT_FAILURE;

    int hh{ in[1] - '0'}, m1{ in[3] - '0'}, m2{ in[4] - '0'}, 
        s1{ in[6] - '0'}, s2{ in[7] - '0'}, f { in[9] - '0'};

    printf( "|%s|%s|%s|%s|%s|%s|\n"
            "|%s|%s|%s|%s|%s|%s|\n"
            "|%s|%s|%s|%s|%s|%s|\n"
            "|%s|%s|%s|%s|%s|%s|\n", 
            OUT(hh,3), OUT(m1,3), OUT(m2,3), OUT(s1,3), OUT(s2,3), OUT(f,3),
            OUT(hh,2), OUT(m1,2), OUT(m2,2), OUT(s1,2), OUT(s2,2), OUT(f,2),
            OUT(hh,1), OUT(m1,1), OUT(m2,1), OUT(s1,1), OUT(s2,1), OUT(f,1),
            OUT(hh,0), OUT(m1,0), OUT(m2,0), OUT(s1,0), OUT(s2,0), OUT(f,0));
}