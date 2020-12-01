#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int result = 0;
char invalid[500][21];
char ISBN[21];

#define ADD_W strcpy(invalid[result], ISBN); ++result; return;

void check(int l, int mod) {
    int sum = 0;
    int tmp = 0;
    for (int c = 0; c < l-1; c++) {
        tmp = ISBN[c] - '0';
        if      ( tmp > 9 ||  tmp < 0 ) { ADD_W;                                   }
        else if ( l == 10             ) { sum += tmp * (10-c);                     }
        else                            { sum += (c % 2 == 0) ? tmp * 1 : tmp * 3; }
    }
    tmp = ISBN[l-1] - '0';
    if      ( ISBN[l-1] == 'X'     )    { sum += 10; if(l == 13) { ADD_W; }        }
    else if ( tmp > 9 || tmp < 0   )    { ADD_W;                                   }
    else                                { sum += tmp;                              }
    if      ( sum % mod != 0       )    { ADD_W;                                   }
}

main() {
    int N; scanf("%d", &N); fgetc(stdin);
    for (int i = 0; i < N; i++) {
         fgets(ISBN, 21, stdin);
         if(ISBN[strlen(ISBN)-1] == '\n') { ISBN[strlen(ISBN)-1] = '\0'; }
         if      ( strlen(ISBN) == 10 ) { check(10, 11); }
         else if ( strlen(ISBN) == 13 ) { check(13, 10); }
         else { strcpy(invalid[result], ISBN); ++result; }
    }
    
    printf("%d invalid:\n", result);
    for (int i = 0; i < result; i++) { printf("%s\n", invalid[i]); }
}