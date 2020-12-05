// Inpired from Alain Delpuch answer
#include <stdio.h>

void f(int n, char *t) {
    int r = n%3;
    n = n/3 + (r==2);
    if (n) f (n,t);
    putchar(t[r]);
}

int TriToInt(const char * tri){
    int c, res = 0;
    while ( c = *tri++ ) {
        switch(c) {
            case '1' : res = 3 * res + 1; break;
            case '0' : res = 3 * res + 0; break;
            case 'T' : res = 3 * res - 1; break;
        }
    }
    return res;
}

main() {
    char l[11], op[6], r[11]; scanf("%s%s%s", l,op,r);
    int a = TriToInt(l), b = TriToInt(r);
    switch (*op) {
        case '<': while (b--) a *= 3; break;
        case '>': while (b--) a /= 3; break;
        case '*': a *= b;             break;
        case '+': a += b;             break;
        case '-': a -= b;             break;
    }
    if (a  >= 0) f( +a,"01T");
    else         f( -a,"0T1");    
}