#include "geom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <cfloat>

using namespace std; 

// GLOBAL VARIABLES
point2d p0; // location of the bottommost point, guaranteed to be an extreme point
const double EPSILON = 1 * pow(10,-6);

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



//how to evaluate whether the value pointed to by a sorts before the value pointed to by b 
//(in which case the compare function should return -1). If the values are equal, then it should 
//return 0 and finally if b should sort before a, the compare should return 1.

// define a comparator for the sorting of all our points
int compare_angles(const void* ppoint1, const void* ppoint2) {

  // redefine point 1 and point 2 as point2d types
  point2d* ppoint1_tmp = (point2d*) ppoint1;
  point2d* ppoint2_tmp = (point2d*) ppoint2;
  point2d point1 = *ppoint1_tmp;
  point2d point2 = *ppoint2_tmp;

  //printf("point1 x being compared: %d\n", point1.x);
  //printf("point1 y being compared: %d\n", point1.y);
  //printf("point2 x being compared: %d\n", point2.x);
  //printf("point2 y being compared: %d\n", point2.y);
  double angle1 = atan2((double) (point1.y - p0.y), (double) (point1.x - p0.x));
  double angle2 = atan2((double) (point2.y - p0.y), (double) (point2.x - p0.x));

  if (angle1 < angle2) {
    //printf("angle 1: %f\n", angle1);
    //printf("angle 2: %f\n", angle2);
    //printf("angle 1 < angle 2\n");
    // we want angle1 (point 1) sorted before angle2 (point 2)
    return -1;
  } 
  if (angle1 > angle2) {
    //printf("angle 1: %f\n", angle1);
    //printf("angle 2: %f\n", angle2);
    //printf("angle 1 > angle 2\n");
    // we want angle2 (point 2) sorted before angle1 (point 1)
    return 1;
  } 
  //dealing with colinear points
  int manhattan_distance_point1 = abs((point1.x - p0.x) + (point1.y - p0.y));
  int manhattan_distance_point2 = abs((point2.x - p0.x) + (point2.y - p0.y));

  //if points 1 and 2 make the same angle and are both right of the x value of p0 or have the same x as p0
  if (angle1 == angle2){
    //check which point is closer
    if((manhattan_distance_point1 < manhattan_distance_point2) || (manhattan_distance_point1 == manhattan_distance_point2)){
      //if point 1 is closer to p0 then sort first
      //printf("on right side, angles are the same, but p1 closer to p0\n");
      return -1;
    }

    else{ //manhattan_distance_point > manhattan_distance_point2
      return 1;
    }
  }
  // it should never reach here, but compiler needs a return statement here
  printf("should never reach here.\n");
  return 0;
}

// compute the convex hull of pts, and store the points on the hull in hull
void graham_scan(vector<point2d>& pts, vector<point2d>& hull ) {

  printf("hull2d (graham scan): start\n"); 
  hull.clear(); //should be empty, but clear it to be safe

  // print all of the points
  for (int i = 0; i<pts.size(); i++) {
    printf("x of point: %d\n", pts[i].x);
    printf("y of point: %d\n", pts[i].y);
  }

  // set point p0 globally
  double minY = DBL_MAX;
  int p0_index;
  for( int i = 0; i < pts.size(); i ++){
    // if it is lower vertically, set it to p0
    if ( pts[i].y < minY){
      minY = pts[i].y;
      p0 = pts[i];
      p0_index = i;
    }
    
    // if the current min y is the same as running min y set current point -> p0 if it is RIGHT of the running p0
    else if(pts[i].y == minY && pts[i].x > p0.x){
      minY = pts[i].y;
      p0 = pts[i];
      p0_index = i;
    }
  }

  // delete p0 from our pts, since it is guaranteed to be an extreme point and doesn't need sorting
  pts.erase(pts.begin() + p0_index); // TODO test that this is working correctly

  //now we have p0 guaranteed to be on the hull, and the remaining points need to be added to hull
  //now we sort points
  printf("RIGHT BEFORE SORTING ORDER:\n");
  // convert vector to an array
  point2d* pts_array = &pts[0];
  for (int i = 0; i<pts.size(); i++) {
    printf("x of point: %d\n", pts[i].x);
    printf("y of point: %d\n", pts[i].y);
  }
  //sort(pts.begin(), pts.end(), compare_angles);  
  qsort((void*) &pts_array[0], pts.size(), sizeof(point2d), compare_angles);
  //print points in sorted order
  printf("SORTED ORDER:\n");
  printf("PO x: %d\n", p0.x);
  printf("PO y: %d\n", p0.y);
  for (int i = 0; i<pts.size(); i++) {
    printf("x of point: %d\n", pts[i].x);
    printf("y of point: %d\n", pts[i].y);
  }

  //assuming hull is acting as our stack
  hull.push_back(p0);
  hull.push_back(pts[0]);
  int i = 1;//does sortedPoints include p0, the index in this line depends on that
  // we dont increment every iteration, because we only want to go to the next element when we add 
  // a point to the hull, not when we pop one off and backtrack
  while (i < pts.size()){
    printf("loop entered\n");
    int top1 = hull.size() - 1;
    int top2 = hull.size() - 2;

    // experimental debugging
    if (hull.size() == 1) {
      printf("hull currently only has p0\n");
      hull.push_back(pts[i]);
      printf("see the hull has 2 elements now\n");
      printf("%lu\n", hull.size());
      i++;
      continue; 
    }
    /* printf("hull[top2] x: %d\n", hull[top2].x);
    printf("hull[top2] y: %d\n", hull[top2].y);
    printf("hull[top1] x: %d\n", hull[top1].x);
    printf("hull[top1] y: %d\n", hull[top1].y);
    printf("pts[i] x: %d\n", pts[i].x);
    printf("pts[i] y: %d\n", pts[i].y); */
    if(left_strictly(hull[top2], hull[top1], pts[i])){//i changed it to strictly_left to deal with colinearity
      printf("pushing pts[i]\n");
      hull.push_back(pts[i]);
      i++; // only incremement after push 
    }
    else{
      printf("popping something\n");
      point2d lastElement = hull.back();
      printf("element being popped x: %d\n", lastElement.x);
      printf("element being popped x: %d\n", lastElement.y);
      hull.pop_back();
      //while points[i] is on right of edge a,b OR points[i] is colinear with edge a,b
      //while(!(left_on(pts[top2], pts[top1], pts[i]))){
       // hull.pop_back();
      //}
      //hull.push_back(pts[i]);
    }
  }

  // if there are 3 collinear points at the end, we want to delete the middle one from the hull
  // TODO - do we need this? 
  /* int hull_size = hull.size();
  if (collinear(p0, hull[hull_size-1], hull[hull_size-2]) == 1) {
    printf("conditional entered.\n");
    hull.pop_back();
  } */

  //return hull
  printf("hull2d (graham scan): end\n"); 
  return; 
}



