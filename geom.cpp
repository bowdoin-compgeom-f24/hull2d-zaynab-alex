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

/* **************************************** */
/* 
 *signed_area2D - this function finds the signed
 *area of the triangle abc. The area is positive if c
 *is to the left of ab, and negative if c is to the right of ab
 *
 *
 *Parameters:
 *-a: a point in the triangle we are taking the signed_area of  
 *-b: a point in the triangle we are taking the signed_area of
 *-c: a point in the triangle we are taking the signed_area of
 *
 *Return:
 *
 * the signed area of triangle abc 
 */
int signed_area2D(point2d a, point2d b, point2d c) {
  int Ax = b.x - a.x; 
  int Ay = b.y - a.y; 
  int Bx = c.x -a.x; 
  int By = c.y - a.y; 
  return (Ax*By) - (Ay*Bx); 
}


/* **************************************** */
/* 
 *collinear - this function determines if points a, b, and c
 *are collinear
 *
 *Parameters:
 *-a: a point we are checking for collinearity 
 *-b: a point we are checking for collinearity
 *-c: a point we are checking for collinearity
 *
 *Return:
 *
 * 1 if p,q,r collinear, and 0 otherwise 
 */
int collinear(point2d p, point2d q, point2d r) {
  int area = signed_area2D(p, q, r);
  if (area == 0){
    return 1;
  }
  return 0;  
}



/* **************************************** */
/* 
 *left_strictly - this function determines if point c is strictly left
 *of the line segment created by points a and b
 *
 *Parameters:
 *-a: one of the points creating the line segment
 *-b: one of the points creating the line segment
 *-c: the point we are checking is left of line segment ab
 *
 *Return:
 *
 * 1 if c is strictly left of ab; 0 otherwise 
 */
int left_strictly(point2d a, point2d b, point2d c) {
  int area = signed_area2D(a, b, c);
  if (area > 0){
    return 1;
  }
  return 0; 
}

/* **************************************** */
/* 
 *left_on - this function determines if point c is left
 *of or on the line segment created by points a and b
 *
 *Parameters:
 *-a: one of the points creating the line segment
 *-b: one of the points creating the line segment
 *-c: the point we are checking is left of or on line segment ab
 *
 *Return:
 *
 * 1 if c is left of ab or on ab; 0 otherwise 
 */
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

/* **************************************** */
/* 
 *compare_angles - this function is a comparator that compares 2
 *points ppoint1 and ppoint2 to determine which should be sorted first
 *
 *Parameters:
 *-ppoint1: one of the points being compared
 *-ppoint2: one of the points being compared
 *
 *Return:
 *
 * -1 if ppoint1 should be sorted first
 * 1 if ppoint2 should be sorted first 
 */
int compare_angles(const void* ppoint1, const void* ppoint2) {

  // redefine point 1 and point 2 as point2d types
  point2d* ppoint1_tmp = (point2d*) ppoint1;
  point2d* ppoint2_tmp = (point2d*) ppoint2;
  point2d point1 = *ppoint1_tmp;
  point2d point2 = *ppoint2_tmp;

  //compute counter clockwise angles of points 1 and 2 with p0 as a reference
  double angle1 = atan2((double) (point1.y - p0.y), (double) (point1.x - p0.x));
  double angle2 = atan2((double) (point2.y - p0.y), (double) (point2.x - p0.x));

  if (angle1 < angle2) {
    // we want angle1 (point 1) sorted before angle2 (point 2)
    return -1;
  } 
  if (angle1 > angle2) {
    // we want angle2 (point 2) sorted before angle1 (point 1)
    return 1;
  } 

  //measuring manhattan distance of points from p0
  int manhattan_distance_point1 = abs((point1.x - p0.x) + (point1.y - p0.y));
  int manhattan_distance_point2 = abs((point2.x - p0.x) + (point2.y - p0.y));
  //if points 1 and 2 make the same angle/are collinear
  if (angle1 == angle2){
    //check if point 1 is closer or if they are the same point
    if((manhattan_distance_point1 < manhattan_distance_point2) || (manhattan_distance_point1 == manhattan_distance_point2)){
      //if so then point 1 should be sorted first
      return -1;
    }
    //else then point 2 is closer and should be sorted first
    else{
      return 1;
    } 
  }
  // it should never reach here, but compiler needs a return statement here
  printf("should never reach here.\n");
  return 0;
}


/* **************************************** */
/* 
 *graham_scan - this computes the convex hull of a vector of points
 *
 *Parameters:
 *-pts: the vector of points that the hull is being computed for
 *-hull: a stack datastructure we are using to pop and push points
 * on the hull
 *
 */
// compute the convex hull of pts, and store the points on the hull in hull
void graham_scan(vector<point2d>& pts, vector<point2d>& hull ) {

  printf("hull2d (graham scan): start\n"); 
  hull.clear(); //should be empty, but clear it to be safe

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
  //now we have p0 guaranteed to be on the hull

  // delete p0 from our pts, since it is guaranteed to be an extreme point and doesn't need sorting
  pts.erase(pts.begin() + p0_index); 

  // convert vector to an array
  point2d* pts_array = &pts[0];
  //now we sort points
  qsort((void*) &pts_array[0], pts.size(), sizeof(point2d), compare_angles);
  
  //push p0 and the first point in sorted pts onto hull
  hull.push_back(p0);
  hull.push_back(pts[0]);
  int i = 1;
  // we dont increment every iteration, because we only want to go to the next element when we add 
  // a point to the hull, not when we pop one off and backtrack
  while (i < pts.size()){
    //indices of 2 most recently added points in hull
    int top1 = hull.size() - 1;
    int top2 = hull.size() - 2;

    // if hull size is ever 1 then add the point we are currently looking at
    if (hull.size() == 1) {
      hull.push_back(pts[i]);
      i++;
      continue; 
    }
    //check if current point is strictly left of the line between the 2 most recently added points in hull 
    if(left_strictly(hull[top2], hull[top1], pts[i])){
      hull.push_back(pts[i]);
      i++; // only incremement after push 
    }
    //if not then pop most recently added point off the hull
    else{
      hull.pop_back();
    }
  }

  printf("hull2d (graham scan): end\n"); 
  return; 
}



