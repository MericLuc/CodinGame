#include <stdio.h>

const char *e;

int t(char a, char b) {
    char c = *e++;
    if ( c == a || c == b ) return 1;
    switch(c) {
        case '(' : case ')' : return t('(',')') && t(a, b);
        case '[' : case ']' : return t('[',']') && t(a, b);
        case '{' : case '}' : return t('{','}') && t(a, b);
        case '<' : case '>' : return t('<','>') && t(a, b);
        case  0  : return 0;
        default  : return t(a, b);
    }
}

main() {
    int N; scanf("%d", &N);
    char expr[10001];
    while ( scanf("%s", expr) == 1 ) { e = expr; printf(t(0,0) ? "true\n" : "false\n"); }
}