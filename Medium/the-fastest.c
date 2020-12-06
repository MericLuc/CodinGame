#include <stdio.h>
#include <string.h>

main() {
    int N; scanf("%d", &N);
    char t[10], res[10] = "99";
    for (int i = 0; i < N && scanf("%s", t); i++) 
        if (strcmp(t,res) < 0) strcpy(res, t);
    printf("%s\n", res);
}