#include <stdio.h>

char arr[11][11];
int  W, H, res = 0;

void check_row(int c, int *r) {
    int res = 0;
    for(int i = 0; i < W; i++) { if(arr[c][i] == '.') { res++; } }
    if(res <= 2){ (*r)++; }
}

void check_col(int c, int *r) {
    int l_res = 0;
    for(int i = 0; i < H; i++) { if(arr[i][c] == '.') { l_res++; } }
    if(l_res <= 2){ (*r)++; }
}

main() {
     scanf("%d%d", &W, &H); fgetc(stdin);
    for (int i = 0; i < H; i++) { scanf("%s",arr[i]); fprintf(stderr, "%s\n", arr[i]); }

    for (int i = 0; i < H-1; i++)
        for (int j = 0; j < W-1; j++)
            if( arr[i  ][j  ] == '.' && arr[i  ][j+1] == '.' &&
                arr[i+1][j  ] == '.' && arr[i+1][j+1] == '.' ) {
                int l_res = 0;
                check_row(i, &l_res); check_row(i+1, &l_res);
                check_col(j, &l_res); check_col(j+1, &l_res);
                if(l_res > res) { res = l_res; }
            }
    printf("%d", res);
}