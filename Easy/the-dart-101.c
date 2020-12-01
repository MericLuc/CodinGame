#include <stdlib.h>
#include <stdio.h>
#include <string.h>

main() {
    int  N; scanf("%d", &N); fgetc(stdin);
    char   pl  [N][1025], turn  [N][1025]; 
    int    sc  [N],       w_turn[N];
    
    for (int i = 0; i < N; i++) { fgets(pl[i]  , 1025, stdin); }
    for (int i = 0; i < N; i++) { fgets(turn[i], 1025, stdin); } 

    for (int i = 0; i < N; i++) {
        fprintf(stderr, "%s%s\n", pl[i], turn[i]);

        w_turn[i]  = 1e9;
        int t_fails = 0, c_fails = 0, c_turn = 0, cmpt = 0, ts = 0;
        char *p     = strtok(turn[i], " ");
        while(p != NULL) {
            cmpt++;
            int tmp    = atoi(p);
            if      ( *p == 'X'    ) {
                sc[i] -= 20;
                if      (++t_fails == 3) { sc[i] = 0;   }
                else if (++c_fails == 2) { sc[i] -= 10; } 
            }
            else {
                c_fails = 0;
                if ( *(p+1) == '*'     ) { tmp = (*p-'0')*atoi(p+2);                                   }
                if ( sc[i] + tmp > 101 ) { t_fails = 0; c_fails = 0; c_turn++; cmpt = 0; sc[i] = ts;   }
                else                     { sc[i] += tmp;                                               }
            }

            if ( sc[i]  == 101           ) { w_turn[i] = c_turn;                                       } 
            if ( cmpt > 0 && cmpt%3 == 0 ) { t_fails = 0; c_fails = 0; c_turn++; cmpt = 0; ts = sc[i]; }
            p = strtok(NULL, " ");
        }
    }
    
    int m_turn  = 1e9, m_index = 0;
    for (int i = 0; i < N; i++)
        if ( w_turn[i] < m_turn ) { m_index = i; m_turn = w_turn[i]; }

    printf("%s", pl[m_index]);
}