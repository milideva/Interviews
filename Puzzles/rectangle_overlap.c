
/*
  Given two rectangles, find if the given two rectangles overlap or not.
  Note that a rectangle can be represented by two coordinates, top left and
  bottom right. So mainly we are given following four coordinates.
*/

#include <stdbool.h>


/*            L2 x, y
              ---------------------- |
              |                      |
              |                      |
              |                      |
   L1 x, y    |                      |
   -----------------------           |
   |          |          |           |
   |          |          |           |
   |           ----------------------  R2 x,y
   |                     |
   ----------------------- R1 x,y

   Assumes that the rectangles are axis-aligned.
   That is parallel to X and Y axis.
   This wont work for axis-unaligned rectangles.
*/


struct point_tag {
    int x;
    int y;
};

typedef struct point_tag point_t;

struct rectangle_tag {
    point_t left;
    point_t right;
};

typedef struct rectangle_tag rectangle_t;

rectangle_t *create_rectangle (int x1, int y1, int x2, int y2) {
    rectangle_t *r = malloc(sizeof(*r));
    if (x1 < x2) {
        r->left.x = x1;
        r->right.x = x2;
        r->left.y = y1;
        r->right.y = y2;
    } else {
        r->left.x = x2;
        r->right.x = x1;
        r->left.y = y2;
        r->right.y = y1;
    }
    printf("Rectangle : left (x:%d, y%d) ... right (x:%d, y%d) \n",
           r->left.x, r->left.y, r->right.x, r->right.y);
    return r;
}

bool rectangle_overlap (rectangle_t *r1, rectangle_t *r2) {

    // If one rectangle is on left side of other 
    if ( (r1->left.x > r2->right.x) || (r2->left.x > r1->right.x) )
        return false;

    // If one rectangle is above other 
    if ( (r1->left.y < r2->right.y) || (r2->left.y < r1->right.y) )
        return false;

    return true;
}

int main () {
    rectangle_t *r1, *r2;
    r1 = create_rectangle(5, 5, 15, 15);
    r2 = create_rectangle(10, 10, 20, 20);
    
    bool overlap = rectangle_overlap(r1, r2);
    printf("overlap:%d\n", overlap);
    return 0;
}
