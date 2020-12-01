#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int W, H, curW, curH;
    
    scanf("%d%d", &W, &H); fgetc(stdin);
    char tab[H][W];
    for (int i = 0; i < H; i++) fgets(tab[i], 1025, stdin);
    

    for( int cmpt_w = 0; cmpt_w < W; cmpt_w += 3 )
    {
        curW = cmpt_w;
        curH = 0;
        while(curH < H-1) {
            curH++;
            fprintf(stderr, "%c\n", tab[curH][curW]);
            if     ( tab[curH][curW] != '|' && 
                     tab[curH][curW] != ' ' &&
                     tab[curH][curW] != '-'   ) { printf("%c%c\n", tab[0][cmpt_w], tab[curH][curW] ); }
            else if( (curW < W - 1) && (tab[curH][curW +1] == '-') ) { curW += 3; }
            else if( (curW > 0)     && (tab[curH][curW -1] == '-') ) { curW -= 3; }
        }
    }

    return 0;
}