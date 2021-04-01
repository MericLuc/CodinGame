// Solution from SatineChatounette

#include <stdio.h>

int check(int g1,int g2,int b,int c)
{
    int g1c[] = { g1%10, (g1/10)%10, (g1/100)%10, (g1/1000)%10 };
    int g2c[] = { g2%10, (g2/10)%10, (g2/100)%10, (g2/1000)%10 };
    int nbb=0, nbc=0;
    int taken[2][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
    for(int i=0;i<4;++i) {
        if(g1c[i]==g2c[i]) {
            taken[0][i] = taken[1][i] = 1;
            ++nbb;
        }
    }
    if(nbb!=b) return 0;
    for(int i=0;i<4;++i) {
        if(taken[0][i]) continue;
        for(int j=0;j<4;++j) {
            if(j==i||taken[1][j]) continue;
            if(g1c[i]==g2c[j]) {
                taken[0][i] = taken[1][j] = 1;
                ++nbc;
                break;
            }
        }
    }
    return (nbc==c);
}

int main()
{
    int N;
    scanf("%d", &N);
    int guesses[100][3];
    for(int i=0;i<N;++i)
        scanf("%d%d%d", &guesses[i][0], &guesses[i][1], &guesses[i][2]);
    for(int i=0;i<=9999;++i) {
        int ok = 1;
        for(int k=0;k<N&&ok;++k)
            if(!check(i,guesses[k][0],guesses[k][1],guesses[k][2]))
                ok = 0;
        if(ok) printf("%0.4d\n",i);
    }
    return 0;
}
