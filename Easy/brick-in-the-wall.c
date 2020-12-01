#include <stdio.h>
int fcomp(int *w_1, int* w_2) { return *w_2 - *w_1; }

void main() {
    int X, N; scanf("%d%d", &X, &N);
    float result = 0;
    int weights[N];

    for (int i = 0; i < N; i++) scanf("%d", &weights[i]);
    qsort(weights, N, sizeof(*weights), fcomp);

    for (int i = 0; i < N; i++) result +=  (i/X) * weights[i];
    printf("%.3f\n", 0.65*result);
}