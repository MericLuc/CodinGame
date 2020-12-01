#include <stdio.h>

int nb_corners, nb_shots;

typedef struct Point {
    int x;
    int y;
};

void check( struct Point* p_shot, struct Point p_array[]) {
    int pos = 0; int neg = 0; int cross_prod = 0;
    for ( int i = 0; i < nb_corners; ++i ) {
        if ( (p_array[i].x == p_shot->x) && (p_array[i].y == p_shot->y) ) { printf("hit\n"); return; }

        int j = (i < nb_corners - 1) ? (i + 1) : 0;
        cross_prod = (p_shot->x - p_array[i].x) * (p_array[j].y - p_array[i].y) - (p_shot->y -p_array[i].y) * (p_array[j].x - p_array[i].x);
        (cross_prod > 0) ? pos++ : neg++;
        
        if ( pos && neg ) { printf("miss\n"); return; }
    }
    printf("hit\n"); return;
}

void main() {
    scanf("%d", &nb_corners);
    struct Point corners[nb_corners];
    struct Point shot;
    for (int i = 0; i < nb_corners; i++) { scanf("%d %d", &corners[i].x, &corners[i].y); }

    scanf("%d", &nb_shots);
    for (int i = 0; i < nb_shots; i++) { scanf("%d %d", &shot.x, &shot.y); check(&shot, corners); }
}