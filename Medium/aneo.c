#include <stdio.h>
#include <math.h>

typedef struct _light { int dst, tim; } light;

main() {
    int   max, lCount; scanf("%d%d", &max, &lCount);
    light lght[lCount];

    for (int i = 0; i < lCount; i++) { scanf("%d%d", &lght[i].dst, &lght[i].tim); }

    do{
        int isOk = 1;
        for (int i = 0; i < lCount; i++)
            if ( (int)floor((3.6*lght[i].dst/max)/lght[i].tim)%2 != 0 ) { isOk = 0; break; }
        if (isOk) { printf("%d", max); break; }
    } while ( max-- );
}