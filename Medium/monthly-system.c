#include <stdio.h>
#include <string.h>

char sub[4], *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

long ctoLong(char *c) {
    long l_conv = 0;
    for(int i = strlen(c)/3 -1; i >= 0; i--) {
        memmove(sub, c, 3); c += 3;
        for(int j = 0; j < 12; j++) { if(!strcmp(sub, months[j])){ l_conv += pow(12,i)*j; break; } }
    }
    return l_conv;
}

void ltoChar(long l) { 
    int ind = 0, r[100] = {0};
    while (l > 0) {  r[ind++] = (l % 12); l /= 12; } 
    
    for(int i = ind-1; i >=0; i--) { printf("%s", months[r[i]]); }
} 

main() {
    int  N; scanf("%d", &N); fgetc(stdin);
    long conv = 0;
    char M[65];
    for (int i = 0; i < N && fgets(M, 65, stdin); i++) { conv += ctoLong(M); }
    ltoChar(conv);
}