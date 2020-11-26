#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char      lab[10][521];
int       w,  h;
long long op, tmp = 0;

typedef enum _Direction {
    TOP   = 1,
    BOT   = 2,
    RIGHT = 3,
    LEFT  = 4
} Dir;

typedef struct _Robot {
    int x_init, y_init;
    int x, y;
    Dir d;
} Rob;

main()
{
    Rob rb = { .x_init = 0, .y_init = 0, .x = 0, .y = 0, .d = TOP };
    scanf("%d%d%lld", &w, &h, &op); fgetc(stdin);

    for     (int i = 0; i < h; i++) { fgets(lab[i], 521, stdin);
        for (int j = 0; j < w; j++)
            if  (lab[i][j] == 'O' ) { rb.x = i; rb.y = j; rb.x_init = i, rb.y_init = j; break; } }

    while(tmp++ < op) {
        switch(rb.d)
        {
            case TOP:   if (lab[--rb.x -1][rb.y      ] == '#') { rb.d = RIGHT; } break;
            case BOT:   if (lab[++rb.x +1][rb.y      ] == '#') { rb.d = LEFT;  } break;
            case RIGHT: if (lab[rb.x     ][++rb.y + 1] == '#') { rb.d = BOT;   } break;
            case LEFT:  if (lab[rb.x     ][--rb.y - 1] == '#') { rb.d = TOP;   } break;
        }
        if (rb.d == TOP && rb.x == rb.x_init && rb.y == rb.y_init) { tmp = op - (op % tmp); }
    }
    prin