#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main() {
    int N; 
    char alignment[8];
    fgets(alignment, 8, stdin);
    scanf("%d", &N); fgetc(stdin);
    char text[N][257];
    int max_length = 0;
    
    for (int i = 0; i < N; i++) { 
        fgets(text[i], 257, stdin); 
        if(text[i][strlen(text[i])-1] == '\n') text[i][strlen(text[i])-1] = 0; 
        max_length = (strlen(text[i]) > max_length) ? strlen(text[i]) : max_length; 
        }

    if      ( alignment[0] == 'L') { for (int i = 0; i < N; i++) printf("%s\n", text[i]); }
    else if ( alignment[0] == 'R' || alignment[0] == 'C' ) { 
        for (int i = 0; i < N; i++) { 
            int spaces = (alignment[0] == 'R') ?  max_length - strlen(text[i]) :  (max_length - strlen(text[i]))/2;
            for (int j = 0; j < spaces; j++) printf(" ");
            printf("%s\n", text[i]); 
        }
    }
    else if ( alignment[0] == 'J' ) { 
        for (int i = 0; i < N; i++) {
            int nwords = 1;
            for (int j = 0; j < strlen(text[i]); ++j) { nwords += (text[i][j] == ' ') ? 1 : 0; }
            if (nwords > 1) {
                float total  = 0;
                int   spaces = 0;
                for (int j = 0; j < strlen(text[i]); ++j) {
                    if (text[i][j] == ' ') {
                        total += (max_length - strlen(text[i]) + nwords-1) / (nwords-1);
                        for (int k = spaces; k < (int)(total); ++k) { spaces++; printf(" "); }
                    }
                    else { printf("%c", text[i][j]); }
                }
                printf("\n");
            }
            else  printf("%s\n", text[i]);
        }
    }
}