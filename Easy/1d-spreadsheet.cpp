#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cell 
{
    char         op;
    int          v1,  v2;
    struct cell *d1, *d2;
    int          calc;
    int          val;
        
    void compute_val(void)
    {
        switch(op)
        {
            case 'V': val = v1     ; break;
            case 'A': val = v1 + v2; break;
            case 'S': val = v1 - v2; break;
            default : val = v1 * v2; break;
        }
        calc = 1;
    }
        
    int eval() 
    {
        if( calc ) { return val;      }
        if( d1   ) { v1 = d1->eval(); }
        if( d2   ) { v2 = d2->eval(); }
            
        compute_val();   
        return val;
    }
};

main()
{
    int N; scanf("%d", &N);

    struct cell *graph = (struct cell*)malloc(N * sizeof(struct cell));

    for (int i = 0; i < N; i++) 
    {
        char op[6], a1[7], a2[7]; scanf("%s%s%s", op, a1, a2);
        graph[i].op = op[0];
        
        if     (a1[0] == '$')             { graph[i].d1 = &graph[atoi(a1+1)];           }
        else                              { graph[i].v1 = atoi(a1); graph[i].d1 = NULL; }

        if     (a2[0] == '$')             { graph[i].d2 = &graph[atoi(a2+1)];           }
        else if(a2[0] != '_')             { graph[i].v2 = atoi(a2); graph[i].d2 = NULL; }

        if(!graph[i].d1 && !graph[i].d2 ) { graph[i].compute_val();                     }
    }
    for (int i = 0; i < N; i++)           { printf("%d\n", graph[i].eval());            }
}