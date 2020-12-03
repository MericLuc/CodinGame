#include <stdio.h>

int prizes[1000];
int memory[1000][20];
int N,R;

int prize(int index, int days ) {
    if ( index == N ) return 0;
    if ( memory[index][days] == 0 ) { 
        int a = ( days == 0 ) ? 0 : prizes[index] + prize( index + 1, days - 1 );
        int b = prize( index + 1, R );
        memory[index][days] = ( a > b ) ? a : b;
    }
    return memory[index][days];
}

main() {
    scanf("%d %d", &N , &R);

    for (int i = 0; i < N; i++) { scanf("%d", prizes+i); }
    printf("%d", prize( 0 , R ));
}