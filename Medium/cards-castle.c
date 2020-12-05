#include <stdio.h>
#include <stdbool.h>

int  H, W;
char S[30][129];

bool stable (int i, int j) {
    switch (S[j][i]) {
        case '/' : return (i != W-1 && S[j  ][i+1] == '\\') &&
                          (j == H-1 || S[j+1][i  ] == '\\');
        case '\\': return (i != 0   && S[j  ][i-1] == '/' ) &&
                          (j == H-1 || S[j+1][i  ] == '/' );
    }
    return true;
}

main() {
    scanf("%d", &H); fgetc(stdin);
    W = H * 2;
    for     (int i = 0; i < H; i++) { fgets(S[i], 129, stdin);       }
    for     (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (!stable(j, i)     ) { printf("UNSTABLE\n"); exit(0); }
    printf("STABLE\n");
}