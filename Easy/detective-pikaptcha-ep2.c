#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum DIR  {
    right = 0,
    bot   = 1,
    left  = 2,
    top   = 3
} _dir;

typedef enum SIDE {
    leftW  = 0,
    rightW = 1
} _side;

char line[103][103], sd[2];
char directions[] = { '>', 'v', '<', '^' };
char sides[]      = { 'L', 'R' };

main()
{
    char tmp[256];
    int  w, h;  scanf("%d%d", &w, &h);
    int pos_x, pos_y;
    int cur_x, cur_y;
    _dir  dir;
    _side side;
    
    for     (int i = 0; i < 103; i++)
        for (int j = 0; j < 103; j++)
            line[i][j] = '#';
            
    for         (int i = 1; i <= h; i++) {
        scanf("%s", tmp);
        for (int t = 0; t < w; t++) { line[i][t+1] = tmp[t]; }
        for     (int j = 1; j <= w; j++) {
            for (int d = 0; d < 4;  d++)
                if(line[i][j] == directions[d]) { pos_x = i; pos_y = j; dir   = d; break; }
        }
    }
    
    for     (int i = 0; i <= h+1; i++) {
        for (int j = 0; j <= w+1; j++) { fprintf(stderr, "%c", line[i][j]); }
        fprintf(stderr, "\n");
    }
    
    scanf("%s", sd);
    side = (sd[0] == sides[0]) ? leftW : rightW;
    cur_x = pos_x; cur_y =  pos_y;
    line[cur_x][cur_y]   = '0';
    
    if( line[cur_x-1][cur_y  ] == '#' &&
        line[cur_x+1][cur_y  ] == '#' &&
        line[cur_x  ][cur_y-1] == '#' &&
        line[cur_x  ][cur_y+1] == '#')
    {
        for    (int i = 1; i <= h; i++) { 
            for(int j = 1; j <= w; j++) { printf("%c", line[i][j]); }
            printf("\n");
        }
        return;
    }
    
    do {
        if(side == leftW)
        {
            switch(dir)
            {
                case right: 
                    if     ( line[cur_x-1][cur_y  ] != '#' ) { cur_x--; dir = top;   }
                    else if( line[cur_x  ][cur_y+1] != '#' ) { cur_y++; dir = right; }
                    else if( line[cur_x+1][cur_y  ] != '#' ) { cur_x++; dir = bot;   }
                    else                                     { cur_y--; dir = left;  }
                    break;
                case bot  :
                    if     ( line[cur_x  ][cur_y+1] != '#' ) { cur_y++; dir = right; }
                    else if( line[cur_x+1][cur_y  ] != '#' ) { cur_x++; dir = bot;   }
                    else if( line[cur_x  ][cur_y-1] != '#' ) { cur_y--; dir = left;  }
                    else                                     { cur_x--; dir = top;   }
                    break;
                case left :
                    if     ( line[cur_x+1][cur_y  ] != '#' ) { cur_x++; dir = bot;   }
                    else if( line[cur_x  ][cur_y-1] != '#' ) { cur_y--; dir = left;  }
                    else if( line[cur_x-1][cur_y  ] != '#' ) { cur_x--; dir = top;   }
                    else                                     { cur_y++; dir = right; }
                    break;
                case top  :
                    if     ( line[cur_x  ][cur_y-1] != '#' ) { cur_y--; dir = left;  }
                    else if( line[cur_x-1][cur_y  ] != '#' ) { cur_x--; dir = top;   }
                    else if( line[cur_x  ][cur_y+1] != '#' ) { cur_y++; dir = right; }
                    else                                     { cur_x++; dir = bot;   }
                default: break;
            }
        }
        else
        {
            switch(dir)
            {
                case right: 
                    if     ( line[cur_x+1][cur_y  ] != '#' ) { cur_x++; dir = bot;   }
                    else if( line[cur_x  ][cur_y+1] != '#' ) { cur_y++; dir = right; }
                    else if( line[cur_x-1][cur_y  ] != '#' ) { cur_x--; dir = top;   }
                    else                                     { cur_y--; dir = left;  }
                    break;
                case bot  :
                    if     ( line[cur_x  ][cur_y-1] != '#' ) { cur_y--; dir = left;  }
                    else if( line[cur_x+1][cur_y  ] != '#' ) { cur_x++; dir = bot;   }
                    else if( line[cur_x  ][cur_y+1] != '#' ) { cur_y++; dir = right; }
                    else                                     { cur_x--; dir = top;   }
                    break;
                case left :
                    if     ( line[cur_x-1][cur_y  ] != '#' ) { cur_x--; dir = top;   }
                    else if( line[cur_x  ][cur_y-1] != '#' ) { cur_y--; dir = left;  }
                    else if( line[cur_x+1][cur_y  ] != '#' ) { cur_x++; dir = bot;   }
                    else                                     { cur_y++; dir = right; }
                    break;
                case top  :
                    if     ( line[cur_x  ][cur_y+1] != '#' ) { cur_y++; dir = right; }
                    else if( line[cur_x-1][cur_y  ] != '#' ) { cur_x--; dir = top;   }
                    else if( line[cur_x  ][cur_y-1] != '#' ) { cur_y--; dir = left;  }
                    else                                     { cur_x++; dir = bot;   }
                default: break;
            }    
        }
        
        line[cur_x][cur_y]++;
    } while(cur_x != pos_x || cur_y != pos_y);
    
    for    (int i = 1; i <= h; i++) { 
        for(int j = 1; j <= w; j++) { printf("%c", line[i][j]); }
        printf("\n");
    }
}