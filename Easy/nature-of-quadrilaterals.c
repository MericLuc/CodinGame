#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct _sPoint {
    int x, y;
} Point;

typedef struct _sQuad {
    char  name[4][2];
    Point pts [4];
} Quad;

int   d( const Point* p1, const Point* p2 ) { // distance between 2 2D points
    return sqrt( pow(p1->x - p2->x,2) + pow(p1->y - p2->y,2) );
}

float a( const Point* v1, const Point* v2 ) { // angle between 2 vectors
    float dot = v1->x*v2->x + v1->y*v2->y;     
    float det = v1->x*v2->y - v1->y*v2->x;
    return atan2(det, dot);
}

bool isPara      ( const Quad* q ) {
    Point vectors[4];   // vectors formed by the 4 sides
    float angles [2];   // angles between opposite sides
    
    vectors[0] = (Point) { .x = q->pts[0].x - q->pts[1].x, .y = q->pts[0].y - q->pts[1].y };
    vectors[1] = (Point) { .x = q->pts[1].x - q->pts[2].x, .y = q->pts[1].y - q->pts[2].y };
    vectors[2] = (Point) { .x = q->pts[2].x - q->pts[3].x, .y = q->pts[2].y - q->pts[3].y };
    vectors[3] = (Point) { .x = q->pts[3].x - q->pts[0].x, .y = q->pts[3].y - q->pts[0].y };
       
    return ( (vectors[0].x*vectors[2].y == vectors[0].y*vectors[2].x  ) &&
             (vectors[1].x*vectors[3].y == vectors[1].y*vectors[3].x) );
}

bool isRhombus   ( const Quad* q ) {
    int s[4]; // size of each side
    for (int i = 0; i < 3; i++) { s[i] = d( &q->pts[i], &q->pts[i+1] ); }
    s[3] = d ( &q->pts[3], &q->pts[0] );

    return ( (s[0]==s[1]) && (s[1]==s[2]) && (s[2]==s[3]) );
}

bool isRectangle ( const Quad* q ) {
    Point vectors[4];   // vectors formed by the 4 sides
    float angles [4];   // angles
    int   s[4];         // size of each side
    for (int i = 0; i < 3; i++) { s[i] = d( &q->pts[i], &q->pts[i+1] ); }
    s[3] = d ( &q->pts[3], &q->pts[0] );
    if ( (s[0] != s[2]) || (s[1] != s[3]) ) { return false; }

    vectors[0] = (Point) { .x = q->pts[0].x - q->pts[1].x, .y = q->pts[0].y - q->pts[1].y };
    vectors[1] = (Point) { .x = q->pts[1].x - q->pts[2].x, .y = q->pts[1].y - q->pts[2].y };
    vectors[2] = (Point) { .x = q->pts[2].x - q->pts[3].x, .y = q->pts[2].y - q->pts[3].y };
    vectors[3] = (Point) { .x = q->pts[3].x - q->pts[0].x, .y = q->pts[3].y - q->pts[0].y };
 
    for (int i = 0; i < 3; i++) { angles[i] = a( &vectors[i], &vectors[i+1] ); }
    angles[3] = a( &vectors[3], &vectors[0] );

    return ( (cos(angles[0]) < 1e-6) && (cos(angles[1]) < 1e-6) && 
             (cos(angles[2]) < 1e-6) && (cos(angles[3]) < 1e-6) );
}

main() {
    int   n; scanf("%d", &n);
    Quad  curr;
    bool para = false; bool rh = false; bool rec = false;
    for (int i = 0; i < n; i++) {
        scanf("%s%d%d%s%d%d%s%d%d%s%d%d", 
              curr.name[0], &curr.pts[0].x, &curr.pts[0].y, 
              curr.name[1], &curr.pts[1].x, &curr.pts[1].y, 
              curr.name[2], &curr.pts[2].x, &curr.pts[2].y, 
              curr.name[3], &curr.pts[3].x, &curr.pts[3].y);
        
        para = isPara     (&curr);
        rh   = isRhombus  (&curr);
        rec  = isRectangle(&curr);
        printf("%c%c%c%c is a ", curr.name[0][0], curr.name[1][0], curr.name[2][0], curr.name[3][0] );
        if ( rh && rec ) { printf("square.\n"        ); }
        else if (rec)    { printf("rectangle.\n"     ); }
        else if (rh)     { printf("rhombus.\n"       ); }
        else if (para)   { printf("parallelogram.\n" ); }
        else             { printf("quadrilateral.\n" ); } 
    }
}