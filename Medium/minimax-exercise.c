#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a<b)?b:a)

typedef struct _Node {
    int  data; 
    bool leaf;
} Node;

Node createNode(int p_data, bool p_bool) { return (Node) { p_data, p_bool }; }

int          D, B, vis = 1;
Node         arr[10000];

int minimax ( int index, int a, int b, bool max ) {
    int val = max ? INT_MIN : INT_MAX;
    Node *p = &arr[index];
    if(p->leaf) { return p->data; }
    if(max)
        for (int i=1; i <= B; i++) { 
            vis++;
            int tmp = minimax(B*index+i, a, b, false);
            val = MAX(val, tmp);
            a   = MAX(a  , val);
            if(a>=b) break;
        }
    else
         for (int i=1; i <= B; i++) { 
            vis++;
            int tmp = minimax(B*index+i, a, b, true);
            val = MIN(val, tmp);
            b   = MIN(b  , val);
            if(a>=b) break;
         }
    return val;
}

main() {
    scanf("%d%d", &D, &B); fgetc(stdin);
    char l[40001], *p; fgets(l, 40001, stdin);
    int cmpt = 0;
    for( int i = 0; i < D; i++ )
        for( int j = 0; j < pow(B,i); j++, cmpt++ )
            arr[cmpt] = createNode(0, false);
    
    p = strtok(l, " ");
    while(p != NULL) {
        arr[cmpt] = createNode(atoi(p), true);
        cmpt++;
        p = strtok(NULL, " ");
    }

    printf("%d ", minimax(0, INT_MIN, INT_MAX, true)); printf("%d\n", vis);
}