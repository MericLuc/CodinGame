#include <stdio.h>

main() {
    int n, m, c, pw=0, maxPw=0, conso[100], seq[100]; scanf("%d%d%d", &n, &m, &c);
    for (int i = 0; i < n; i++) { scanf("%d", &conso[i]); }
    for (int i = 0; i < m; i++) { 
        scanf("%d", &seq[i]  ); 
        pw              += conso[seq[i]-1];
        conso[seq[i]-1] *=-1;
        if ( pw > maxPw ) maxPw = pw;
    }

    printf("Fuse was %sblown.\n", (maxPw > c)? "" : "not ");
    if ( !(maxPw > c) ) printf("Maximal consumed current was %d A.\n", maxPw);
}