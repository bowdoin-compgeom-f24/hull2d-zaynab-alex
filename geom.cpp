#include "geom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>

using namespace std; 

// GLOBAL VARIABLES
point2d p0; // location of the bottommost point, guaranteed to be an extreme point

/* **************************************** */
/* returns the signed area of triangle abc. The area is positive if c
   is to the left of ab, and negative if c is to the right of ab
 */
int signed_area2D(point2d a, point2d b, point2d c) {
  int Ax = b.x - a.x; 
  int Ay = b.y - a.y; 
  int Bx = c.x -a.x; 
  int By = c.y - a.y; 
  return (Ax*By) - (Ay*Bx); 
 
}



/* **************************************** */
/* return 1 if p,q,r collinear, and 0 otherwise */
int collinear(point2d p, point2d q, point2d r) {
  int area = signed_area2D(p, q, r);
  if (area == 0){
    return 1;
  }
  return 0;  
}



/* **************************************** */
/* return 1 if c is  strictly left of ab; 0 otherwise */
int left_strictly(point2d a, point2d b, point2d c) {
  int area = signed_area2D(a, b, c);
  if (area > 0){
    return 1;
  }
  return 0; 
}


/* return 1 if c is left of ab or on ab; 0 otherwise */
int left_on(point2d a, point2d b, point2d c) {
  int area = signed_area2D(a, b, c);
  if (area >= 0){
    return 1;
  }
  return 0; 
}

vector<point2d>& initializer(vector<point2d>& pts, vector<point2d>& hull){
  printf("hull2d (graham scan): start\n");
  hull.clear(); //should be empty, but clear it to be safe


 //just for fun: at the moment we set the hull as the bounding box of
 //pts.  erase this and insert your code instead
  int x1, x2, y1, y2;
  if (pts.size() > 0) {
    x1 = x2 = pts[0].x;
    y1 = y2 = pts[0].y;
    
    for (int i=1; i< pts.size(); i++) {
      if (pts[i].x < x1) x1 = pts[i].x;
      if (pts[i].x > x2) x2 = pts[i].x;
      if (pts[i].y < y1) y1 = pts[i].y;
      if (pts[i].y > y2) y2 = pts[i].y;
    }
    point2d p1 = {x1,y1}, p2 = {x2, y1}, p3 = {x2, y2}, p4 = {x1, y2};
    hull.push_back(p1);
    hull.push_back(p2);
    hull.push_back(p3);
    hull.push_back(p4);
  }
  printf("hull2d (graham scan): end\n");
  return hull;
}


//how to evaluate whether the value pointed to by a sorts before the value pointed to by b 
//(in which case the compare function should return -1). If the values are equal, then it should 
//return 0 and finally if b should sort before a, the compare should return 1.

// define a comparator for the sorting of all our points
int compare_angles(point2d point1, point2d point2) {
  double angle1 = (double) (point1.y - p0.y) / (point1.x - p0.x); // double check its a float
  double angle2 = (double) (point2.y - p0.y) / (point2.x - p0.x);

  if (angle1 < angle2) {
    // we want angle1 sorted before angle2
    return -1;
  } 
  if (angle1 > angle2) {
    // we want angle2 sorted before angle1
    return 1;
  } 
  //dealing with colinear points
  double manhattan_distance_point1 = (point1.x - p0.x) + (point1.y - p0.y);
  double manhattan_distance_point2 = (point2.x - p0.x) + (point2.y - p0.y);

  //if points 1 and 2 are both right of he x value of p0 or have the same x as p)
  if ((point1.x >= p0.x) && (point2.x >= p0.x) ){
    //check which point is closer
    if(manhattan_distance_point1 < manhattan_distance_point2){
      //if point 1 is closer to p0 then sort first
      return -1;
    }
    else{
      //point 2 is closer so sort it first
      return 1;
    }
  }
  //if points 1 and 2 are left of the x value of p0
  else{
    //check which point is closer
    if(manhattan_distance_point1 > manhattan_distance_point2){
      //if point 1 is further from p0 so sort it first
      return -1;
    }
    else{
      //point 2 is further from p0 so sort it first
      return 1;
    }
  }
    

}

// compute the convex hull of pts, and store the points on the hull in hull
void graham_scan(vector<point2d>& pts, vector<point2d>& hull ) {
  //Algorithm GrahamScan (input: points P )
    //Find interior point p0 (instead of an interior point, can pick the lowest point)
    //Sort all other points ccw around p0; denote them p1, p2, ...pn−1 in this order.
    //Initialize stack S = (p2, p1)
    //for i = 3 to n-1 do
     //if pi is left of (second(S), first(S)): 
        //push pi on S
     //else:
       //repeat: pop S while pi is right of (second(S), first(S))
       //push pi on S

  printf("hull2d (graham scan): start\n"); 
  hull.clear(); //should be empty, but clear it to be safe

  // set point p0 globally
  int minY = 10000;
  for( int i = 0; i < pts.size(); i ++){
    if ( pts[i].y < minY){
      minY = pts[i].y;
      p0 = pts[i];
    }
    else if(pts[i].y == minY && pts[i].x > p0.x){
      minY = pts[i].y;
      p0 = pts[i];
    }

  }
  //now we have p0 guaranteed to be on hull
  //now we sort points
  //sort takes 2 more parameters but im confused as to how they work
  sort(compare_points);
  //assuming hull is acting as our stack
  hull.push_back(p0);
  hull.push_back(sortedPoints[1]);//does sortedPoints include p0, the index in this line depends on that
  int top1 = sortedPoints.size() - 1;
  int top2 = sortedPoints.size() - 2;
  for (int i = 3; i < sortedPoints.size(); i++){//is it really i = 3?
    if(left_on(sortedPoints[top2], sortedPoints[top1], sortedPoints[i])){
      hull.push_back(sortedPoints[i]);
    }
    else{
      hull.pop_back();
      //while points[i] is on right of edge a,b
      while(!(left_on(sortedPoints[top2], sortedPoints[top1], sortedPoints[i]))){
        hull.pop_back();
      }
      hull.push_back(sortedPoints[i]);
    }
  }
  //return hull
  printf("hull2d (graham scan): end\n"); 
  return; 
}



