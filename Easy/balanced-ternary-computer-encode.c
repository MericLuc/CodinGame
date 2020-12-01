#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

char* reverse(char* s) {    
    int len = strlen(s);
    char l_out[len];
    
    for (int i = 0; i < len; ++i) l_out[i] = s[len - 1 - i];
    l_out[len] = '\0';
    strncpy(s, l_out, sizeof(l_out));
}

void negate(char* s) {
    for (int i = 0; i < strlen(s); ++i)  
            if      (s[i] == '1') s[i] = 'T';
            else if (s[i] == 'T') s[i] = '1';
}

int main()
{
    int  N;
    bool negativ(false);
    char l_return[10] = "";
    scanf("%d", &N);
    
    if (N == 0) append(l_return, '0');
    else {
        if (N < 0) { negativ = true; N = -N; }
        while( N != 0)
        {
            int rest = N % 3;
            
            if     (rest == 0) append(l_return, '0');
            else if(rest == 1) append(l_return, '1');
            else {
                append(l_return, 'T');
                N++;
            }
             N /= 3;
        }
        if (negativ) negate(l_return);
    }
    
    printf("%s\n", reverse(l_return) );

    return 0;
}