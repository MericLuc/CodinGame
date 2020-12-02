#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int  chartoInt(const char c) { return ((c == '@') ? 1 : 0);   }
char inttoChar(const int i)  { return ((i == 1) ? '@' : '.'); }
int  getIndex(const char c1, const char c2, const char c3 ) { return 4*chartoInt(c1) + 2*chartoInt(c2) + chartoInt(c3); }

void main() {
    int R, N, code[8]; 
    char startPattern[51]; char tmpPattern[51];
    scanf("%d%d%s", &R, &N, startPattern);

    for (int i = 0; i < 8; ++i) code[i] = ( R >> i ) & 1;

    while(N--) {
        printf("%s\n", startPattern);
        tmpPattern[0] = inttoChar(code[getIndex( startPattern[strlen(startPattern)-1], startPattern[0], startPattern[1] )]);
        for (int j = 1; j < strlen(startPattern)-1; ++j) { tmpPattern[j] = inttoChar(code[getIndex( startPattern[j-1], startPattern[j], startPattern[j+1] )]); }
        tmpPattern[strlen(startPattern)-1] = inttoChar(code[getIndex( startPattern[strlen(startPattern)-2], startPattern[strlen(startPattern)-1], startPattern[0]) ]);
        strcpy(startPattern, tmpPattern);
    }
}