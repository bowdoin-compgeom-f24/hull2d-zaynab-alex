#ifndef __geom_h
#define __geom_h

#include <vector>

using namespace std; 


typedef struct _point2d {
  int x,y; 
} point2d;


// debug try adding points
extern vector<point2d>  points;



/* returns 2 times the signed area of triangle abc. The area is
   positive if c is to the left of ab, 0 if a,b,c are collinear and
   negative if c is to the right of ab
 */
int signed_area2D(point2d a, point2d b, point2d c); 


/* return 1 if p,q,r collinear, and 0 otherwise */
int collinear(point2d p, point2d q, point2d r);


/* return 1 if c is  strictly left of ab; 0 otherwise */
int left_strictly (point2d a, point2d b, point2d c); 


/* return 1 if c is left of ab or on ab; 0 otherwise */
int left_on(point2d a, point2d b, point2d c); 



// compute the convex hull 
void graham_scan(vector<point2d>& pts, vector<point2d>& hull);
  

#endif
