#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void readAlphabet(char M[20][2000], int L, int H) 
{
    for (int y = 0; y < H; y++) 
    {
        char numeral[2048];
        scanf("%s", numeral);
        fgetc(stdin);

        for (int i = 0; i < 20; i++)
            for (int x = 0; x < L; x++) M[i][y * L + x] = numeral[i * L + x];
    }
}

long long int readNum(char M[20][2000], int L, int H) 
{

    char tmp[2000];
    long long int R = 0;
    int S;
    scanf("%d", &S);
    fgetc(stdin);

    long long int b = pow(20, S / H - 1);

    for (int i = 0; i < S;) {

        for (int y = 0; y < H; y++) { scanf("%s", (tmp + y * L)); fgetc(stdin); }

        for (int j = 0; j < 20; j++)
            if (0 == memcmp(M[j], tmp, H * L)) { R+= b * j; break; }
        
        b/= 20;
        i+= H;
    }
    return R;
}

void printNum(char M[20][2000], int L, int H, long long int n) {

    long long int nums[16] = {0}; // log20(2^64)

    int i = 0;

    if (n == 0)
        i++;

    while (n) {

        long long int t = n / 20;
        long long int r = n - t * 20;

        nums[i++] = r;
        n = t;
    }

    while (i > 0) {

        n = nums[--i];

        for (int j = 0; j < L * H; j++) {

            printf("%c", M[n][j]);

            if ((j % L) == (L - 1)) {
                printf("\n");
            }
        }
    }
}

int main() 
{
    int L, H;
    char M[20][2000];
    char OP;
    long long int N1, N2;

    scanf("%d%d", &L, &H);
    fgetc(stdin);

    readAlphabet(M, L, H);

    N1 = readNum(M, L, H);
    N2 = readNum(M, L, H);

    scanf("%c", &OP);
    fgetc(stdin);

    switch (OP) {
        case '+':
            printNum(M, L, H, N1 + N2);
            break;
        case '*':
            printNum(M, L, H, N1 * N2);
            break;
        case '-':
            printNum(M, L, H, N1 - N2);
            break;
        case '/':
            printNum(M, L, H, N1 / N2);
            break;
    }
    return 0;
}