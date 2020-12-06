#include <stdio.h>
#include <string.h>

typedef struct _radar { char imm[8]; int d;  long ts; } radar; 

main() {
    int L, N, d, nb = 0; scanf("%d%d", &L, &N); fgetc(stdin);
    radar r[N], c;
    char tmp[256], *it;
    for (int i = 0; i < N && fgets(tmp, 256, stdin); i++) {
        it = strtok(tmp, " ");
        memmove(c.imm, it, sizeof(it));
        c.d  = atoi( strtok(NULL, " ") );
        c.ts = atol( strtok(NULL, " ") );

        if ( i > 0 && !strcmp(c.imm, r[i-1].imm) && (3600.f*(c.d - r[i-1].d)/(c.ts - r[i-1].ts) > L) ) { 
            nb++; printf("%s %d\n", c.imm, c.d); 
        }
        r[i] = c;
    }
    if(nb == 0) printf("OK\n");
}