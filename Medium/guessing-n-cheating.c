#include <stdio.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

main() {
    int R, guess, answer, min = 1, max = 100, cheating = 0;
    scanf("%d", &R); fgetc(stdin);

    for (int i = 0; i < R; i++) {
        char line[256]; fgets(line, 256, stdin);
        char *p       = strtok(line, " ");
        guess         = atoi(p);
        p             = strtok(NULL, "");

        if      (  *(p+4) == 'h' ) { max = MIN(max, guess - 1); }
        else if (  *(p+4) == 'l' ) { min = MAX(min, guess + 1); }
        
        if ( (max < min) || ((*(p+4) == 't') && !(min <= guess && guess <= max)) ) {
            printf("Alice cheated in round %d\n", i+1);
            cheating = 1;
            break;
        }
    }
    if(cheating == 0) printf("No evidence of cheating");
}