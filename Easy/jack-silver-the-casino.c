#include <stdio.h>
#include <math.h>

main() {
    int r, c, roulette, curr_number, bet;
    scanf("%d %d", &r, &c);

    for (int i = 0; i < r; i++) {
        char turn[1025]; scanf("%d %s",&roulette, turn);
        bet = ceil(c/4.f);
        c -= bet;
        
        if      ( *turn == 'E' ) {
             if (roulette && (roulette & 1) == 0) { c += 2*bet;  } }
        else if ( *turn == 'O' ) {
             if (roulette & 1)                    { c += 2*bet;  } }
        else if ( *turn == 'P' ) {
            scanf("%d", &curr_number);
             if (roulette == curr_number)         { c += 36*bet; } }
    }
    printf("%d\n", c);
}