#include <stdio.h>

#define MIN(a,b)((a<b)?a:b)

typedef struct _cage { int s, h, a; } cage;

void update ( cage* c ) {
    if ( c->a == 0 ) { return; }
    int new_sick = MIN( c->h, 2 * c->s );
    c->s  = new_sick; 
    c->h -= new_sick; 
    c->a  = c->s + c->h;
}

main() {
    int  N, Y; scanf("%d%d", &N, &Y);
    cage c[N];
    for (int i = 0; i < N; i++) { scanf("%d%d%d", &c[i].s, &c[i].h, &c[i].a); }
    
    for (int i = 0; i < Y; i++) { 
        int res = 0;
        for ( int j = 0; j < N; j++ ) { update(&c[j]); res += c[j].a; } 
        if ( res == 0 )               { printf("0\n"); break;         }
        printf("%d\n", res);
    }
}