/* viewpoints.cpp, Laura Toma
   
   What it does: Draws a set of points in the default 2D ortho
   projection.  Includes a tentative function for printing and drawing
   a list of points (assumed to be a convex hull).
   
   This code is provided as a startup for your 2d hull.  Change it as
   needed to work with your project.
*/

#include "geom.h"
#include "rtimer.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <strings.h>
#include <cmath>

//to compile on both apple and unix platform
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
using namespace std; 




//pre-defined colors for convenience 
GLfloat red[3] = {1.0, 0.0, 0.0};
GLfloat green[3] = {0.0, 1.0, 0.0};
GLfloat blue[3] = {0.0, 0.0, 1.0};
GLfloat black[3] = {0.0, 0.0, 0.0};
GLfloat white[3] = {1.0, 1.0, 1.0};
GLfloat gray[3] = {0.5, 0.5, 0.5};
GLfloat yellow[3] = {1.0, 1.0, 0.0};
GLfloat magenta[3] = {1.0, 0.0, 1.0};
GLfloat cyan[3] = {0.0, 1.0, 1.0};
/* from https://www.opengl.org/discussion_boards/showthread.php/132502-Color-tables  */
GLfloat brown[3] = { 0.647059, 0.164706, 0.164706}; 
GLfloat DarkBrown[3] = { 0.36, 0.25, 0.20}; 
GLfloat DarkTan[3] = { 0.59, 0.41, 0.31};
GLfloat Maroon[3]= { 0.556863, 0.137255, 0.419608}; 
GLfloat DarkWood[3] = { 0.52, 0.37, 0.26}; 
GLfloat  Copper[3] = { 0.72,  0.45,  0.20};
GLfloat green1[3] = {.5, 1, 0.5};
GLfloat green2[3] = {0.0, .8, 0.0};
GLfloat green3[3] = {0.0, .5, 0.0};
GLfloat ForestGreen[3] = { 0.137255, 0.556863, 0.137255};
GLfloat MediumForestGreen[3] = { 0.419608 , 0.556863 , 0.137255}; 
GLfloat LimeGreen[3] ={ 0.196078,  0.8 , 0.196078}; 
GLfloat Orange[3] = { 1, .5, 0}; 
GLfloat Silver[3] = { 0.90, 0.91, 0.98};
GLfloat Wheat[3] = { 0.847059 , 0.847059, 0.74902}; 





/* global variables */

//desired number of points, entered by the user on the command line
int NPOINTS;

//the vector of points
//note: needs to be global in order to be rendered
vector<point2d>  points;

//the convex hull 
//note: needs to be global in order to be rendered
vector<point2d>  hull; 



//window size for the graphics window
const int WINDOWSIZE = 500; 

/* currently there are 4 different ways to initialize points.  The
   user can cycle through them by pressing 'i'. Check out the display()
   function.
*/
int NB_INIT_CHOICES = 15; 
int  POINT_INIT_MODE = 0; //the first inititalizer





/********************************************************************/
/* forward declarations of functions */

//print label, then the vector 
void print_vector(const char* label, vector<point2d> p); 


/* render the points. Each point is drawn as a small square.  */
void draw_points(vector<point2d> pts); 

/* Render the hull; the points on the hull are expected to be in
   boundary order (either ccw or cw), otherwise it will look
   zig-zaagged.  
*/
  void draw_hull(vector<point2d> hull); 


void display(void);
void keypress(unsigned char key, int x, int y);

// initializer function
void initialize_points_circle(vector<point2d>& pts, int n); 
void initialize_points_horizontal_line(vector<point2d>&pts, int n);
void initialize_points_random(vector<point2d>&pts, int n) ;
void initialize_points_cross(vector<point2d>&pts, int n) ;

//you'll add more 
// our cases
void initialize_points_heart(vector<point2d>& pts, int n); 
void initializer_square(vector<point2d>& pts, int n);

// class cases
void initialize_points_2(vector<point2d>& pts, int n);
void initialize_points_thin_cross(vector<point2d>& pts, int n);
void initialize_points_stripes(vector<point2d>& pts, int n);
void initialize_points_spiral(vector<point2d>& pts, int n);
void initialize_points_wave(vector<point2d>& pts, int n);

// extra testing cases
void initialize_points_hardcoded_triangle(vector<point2d>& pts, int n);
void initialize_points_two_vertical(vector<point2d>& pts, int n);
void initialize_points_vertical_line(vector<point2d>& pts, int n);


/********************************************************************/

/* ****************************** */
/*Given initializers to test on*/
/* ****************************** */

/* ****************************** */
/* Initializes pts with n points on two circles.  The points are in the
   range [0, WINSIZE] x [0, WINSIZE].
*/ 
void initialize_points_circle(vector<point2d>& pts, int n) {

  printf("\ninitialize points circle\n"); 
  //clear the vector just to be safe 
  pts.clear(); 

  n = n/2; //we'll generaate two circles, n/2 points each
  double  step = 2* M_PI/n; 
  int radius = 100; 

  point2d p; 
  for (int i=0; i<n; i++) {
    p.x = WINDOWSIZE/2+ radius*cos(i*step); 
    p.y = WINDOWSIZE/2+ radius*sin(i*step); 
    pts.push_back(p); 
  }

  radius /= 2; 
  for (int i=0; i<n; i++) {
    p.x = WINDOWSIZE/2+ radius*cos(i*step); 
    p.y = WINDOWSIZE/2+ radius*sin(i*step); 
    pts.push_back(p); 
  }
  
}


/* ****************************** */
/* Initializes pts with n points on a line.  The points are in the
   range [0, WINSIZE] x [0, WINSIZE].
*/ 
void initialize_points_horizontal_line(vector<point2d>& pts, int n) {

  printf("\ninitialize points line\n"); 
  //clear the vector just to be safe 
  pts.clear(); 
  
  point2d p; 
  for (int i=0; i<n; i++) {
    p.x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 
    p.y =  WINDOWSIZE/2; 
    pts.push_back(p); 
  }
}


/* ****************************** */
/* Initializes pts with n random points.  The points are in the
   range [0, WINSIZE] x [0, WINSIZE].
*/ 
void initialize_points_random(vector<point2d>& pts, int n) {

   printf("\ninitialize points random\n"); 
  //clear the vector just to be safe 
  pts.clear(); 

  point2d p; 
  for (int i=0; i<n; i++) {
    p.x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 
    p.y =  (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
    pts.push_back(p); 
  }
}


/* ****************************** */
/* Initializes pts with n points on a cross-like shape.  The points are
   in the range (0,0) to (WINSIZE,WINSIZE).
*/ 
void initialize_points_cross(vector<point2d>& pts, int n) {
  
  printf("\ninitialize points cross\n"); 
  //clear the vector just to be safe 
  pts.clear(); 
  
  point2d p; 
  for (int i=0; i<n; i++) {
    if (i%2 == 0) {
      
      p.x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 
      p.y =  random() % ((int)(.7*WINDOWSIZE))  / 5;
      p.y += (int)((1-.7/5)*WINDOWSIZE/2);
    };
    if (i%2 == 1)  {
      
      p.x = random() % ((int)(.7*WINDOWSIZE)) / 5; 
      p.x +=  (int)((1-.7/5)*WINDOWSIZE/2);
      p.y =  (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
    }
   
    pts.push_back(p); 
    
  }

}



/* ****************************** */
/*    Our written initializers    */
/* ****************************** */

/* ****************************** */
/* Initializes n points in the shape of a heart, scaled to fit the majority of the window.
 * Used equation from Wolfram MathWorld link in slack to specify the heart equation.
*/ 
void initialize_points_heart(vector<point2d>& pts, int n) {

  printf("\ninitialize points heart\n"); 
  pts.clear(); // clear it out for safety

  double t = (2*M_PI) / n; // defining step size this way will give us n points
  point2d p;
  int SCALING_FACTOR = 100; // ensures that the heart is a good size

  for (double a = 0; a<2*M_PI; a+=t) {
    p.x = WINDOWSIZE/2 + SCALING_FACTOR*(sqrt(2) * sin(a)*sin(a)*sin(a))+ (random() % ((int)(.07*WINDOWSIZE)));
    p.y = WINDOWSIZE/2 + SCALING_FACTOR*(-cos(a)*cos(a)*cos(a) - cos(a)*cos(a) + 2*cos(a)) + (random() % ((int)(.07*WINDOWSIZE)));
    pts.push_back(p);
  }
}


/* ****************************** */
/* Initializes a square of 25 hardcoded points, evenly spaced out, in the middle of the window. 
 * these points are in the form of a square that is 100 x 100. Additionally, adds 
 * n_additional_points randomly generated to the middle of the square. Tests collinearity. 
*/ 
void initializer_square(vector<point2d>& pts, int n_additional_points){
  
  pts.clear(); //should be empty, but clear it to be safe
  for(int i = 200; i <= 300; i+=20){
    for(int j = 200; j <= 300; j+=20){
      point2d p;
      p.x = i;
      p.y = j;
      pts.push_back(p);
    }
  }
  //we are using user input to create n points in addition to our hard coded collinear points
  for (int i=0; i<(n_additional_points); i++) {
    point2d p_rand;
    p_rand.x = (int)200 + random() % ((int)(100)); 
    p_rand.y =  (int)200 + random() % ((int)(100));
    pts.push_back(p_rand); 
  }
}


/* ****************************** */
/*  Five initializers from class  */
/* ****************************** */

//1. tom's example
void initialize_points_2(vector<point2d>&pts, int n){
  printf("\ninitialize points 2\n"); 
  pts.clear();
  assert(pts.size() == 0);

  point2d p;
  int x_noise, y_noise;
  int pos, pos2;
  for (int i = 0; i < n; i++)
  {
    switch (i % 3) {
      case 0:
        p.x = (int)(0.25*WINDOWSIZE) + random() % ((int)(0.5*WINDOWSIZE));
        p.y = (int) (0.15*WINDOWSIZE);
        break;
      case 1:
        pos = random() % (int)(0.5*WINDOWSIZE);
        p.x = pos; p.y = pos;
        p.x += (int) (0.25*WINDOWSIZE);
        p.y += (int) (0.15*WINDOWSIZE);
        break;
      case 2: 
        pos2 = random() % 180;
        p.x = (int)(0.5 * WINDOWSIZE) + (int) ((0.25*WINDOWSIZE) * cos((M_PI * pos2)/180));
        p.y = (int)(0.65 * WINDOWSIZE) + (int) ((0.25*WINDOWSIZE) * sin((M_PI * pos2)/180));
        break;
    }
    x_noise = random() % ((int) (0.05*WINDOWSIZE));
    y_noise = random() % ((int) (0.05*WINDOWSIZE));
    p.x += x_noise;
    p.y += y_noise;
    pts.push_back(p);
  }
}

//2. Max and Abhi's example
void initialize_points_thin_cross(vector<point2d>&pts, int n) {
  printf("\ninitialize points thin cross\n");
  pts.clear();
  point2d p;
  for (int i = 0; i < n; i++) {
    // put points on horizontal line
    if (i % 2 == 0) {
      p.x = random() % (int)(WINDOWSIZE);
      p.y = WINDOWSIZE/2;
    }
    // put points on vertical line
    if (i % 2 == 1) {
      p.x = WINDOWSIZE/2;
      p.y = random() % (int)(WINDOWSIZE);
    }
    pts.push_back(p);
  }
}

//3. Leah's example
void initialize_points_stripes(vector<point2d>& pts, int n) {
  printf("\ninitialize points stripes\n"); 
  pts.clear();
  double step = WINDOWSIZE/n;
  n = n/2;

  point2d p;
  point2d q; 
  for (int i = 0; i < n; i++) {
    float t = step*i;
    p.x = t + WINDOWSIZE/4;
    p.y = t + WINDOWSIZE/5;
    q.x = t + WINDOWSIZE/4;
    q.y = t + 2*WINDOWSIZE/5;
    pts.push_back(p); 
    pts.push_back(q); 
  }
}

// 4. David's example
/* ****************************** */
/* Initializes pts with n points forming a spiral shape. 
   The points are in the range [0, WINSIZE] x [0, WINSIZE].
*/ 
void initialize_points_spiral(vector<point2d>& pts, int n) {
    printf("\ninitialize points spiral\n");
    pts.clear(); 

    double centerX = WINDOWSIZE / 2; // center of circle
    double centerY = WINDOWSIZE / 2; // center of circle
    
    double theta_increment = 1 / M_PI; // angle increment for the spiral
    double max_radius = WINDOWSIZE / 2.5; // maximum radius to keep the spiral within bounds
    double radius_increment = max_radius / (n / 10.0); // increment based on number of points

    for (int i = 0; i < n; i++) {
        double theta = i * theta_increment * 0.5; // angle increases as i increases
        double radius = radius_increment * i * 0.1; // scale the radius to keep it spiral-like
        radius = fmin(radius, max_radius);  // ensures the radius doesn't exceed the boundary

        point2d p;
        p.x = centerX + radius * cos(theta); 
        p.y = centerY + radius * sin(theta); 
        
        pts.push_back(p); 
    }
}

// 5. Manny and Jack's example
void initialize_points_wave(vector<point2d>& pts, int n){
printf("\ninitialize points wave\n");
  //clear the vector just to be safe
  pts.clear();
  double step = (double)WINDOWSIZE / n;
  double amplitude = 100;  // Height of the wave
  double frequency = 0.1;  // Controls the number of waves
  point2d p;
  for (int i = 0; i < n; ++i) {
    p.x = i * step;
    p.y = WINDOWSIZE / 2 + amplitude * sin(frequency * p.x);
    pts.push_back(p);
  }
}


/* ****************************** */
/*       extra initializers       */
/* ****************************** */

/* ****************************** */
/* Initializes 5 points in the shape of a right triangle. This test case is intended to test 
 * the algorithm for multiple cases of collinearity that could cause problems.
*/ 
void initialize_points_hardcoded_triangle(vector<point2d>& pts, int n) {

  printf("\ninitialize points hard-coded\n"); 
  pts.clear(); // clear it out for safety

  point2d point1;
  point1.x = 0; 
  point1.y = 0;
  pts.push_back(point1);

  point2d point2;
  point2.x = 50; 
  point2.y = 50;
  pts.push_back(point2);

  point2d point3;
  point3.x = 100; 
  point3.y = 100;
  pts.push_back(point3);

  point2d point4;
  point4.x = 0; 
  point4.y = 100;
  pts.push_back(point4);

  point2d point5;
  point5.x = 0; 
  point5.y = 50;
  pts.push_back(point5);
}

/* ****************************** */
/* This is a test case from Ziyou, posted in slack. This test case is intended to test 
 * the algorithm for multiple cases of collinearity that could cause problems.
*/ 
void initialize_points_two_vertical(vector<point2d>& pts, int n) {
  
  printf("\ninitialize points that make two vertical lines.\n"); 
    //clear the vector just to be safe 
  pts.clear(); 
  
  point2d p; 
  for (int i=0; i<n/2; i++) {
    p.y = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 
    p.x =  WINDOWSIZE/2; 
    pts.push_back(p); 
  }
    for (int i=0; i<n/2; i++) {
    p.y = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 
    p.x =  WINDOWSIZE/4; 
    pts.push_back(p); 
  }
}

/* ****************************** */
/* Initializes n points in a vertical line: intended to test issues with a single line, i.e. 
* a shape that only has 2 vertices.
*/ 
void initialize_points_vertical_line(vector<point2d>& pts, int n) {

  printf("\ninitialize points vertical line\n"); 
  //clear the vector just to be safe 
  pts.clear(); 
  
  point2d p; 
  for (int i=0; i<n; i++) {
    p.y = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 
    p.x =  WINDOWSIZE/2; 
    pts.push_back(p); 
  }
}


/* ****************************** */
/* print the vector of points */
void print_vector(const char* label, vector<point2d> points) {
  
  printf("%s ", label);
  for (int i=0; i< points.size(); i++) {
    printf("[%3d,%3d] ", points[i].x, points[i].y);
  }
  printf("\n");
}





/* ****************************** */
int main(int argc, char** argv) {

  //read number of points from user
  if (argc!=2) {
    printf("usage: viewPoints <nbPoints>\n");
    exit(1); 
  }
  NPOINTS = atoi(argv[1]); 
  printf("you entered n=%d\n", NPOINTS);
  assert(NPOINTS >0); 

  /* populate screen with points in a pattern of your choosing 
   * based off of the initializers defined above 
   */

  // NOTE: CHANGE THIS BELOW TO THE SET OF POINTS YOU WANT TO INITIALIZE AND COMPUTE C. HULL FOR
  initialize_points_random(points, NPOINTS);

  //compute the convex hull 
  Rtimer rt1; 
  rt_start(rt1); 
  graham_scan(points, hull); 
  rt_stop(rt1); 
  print_vector("hull:", hull);
  
  //print the timing 
  char buf [1024]; 
  rt_sprint(buf,rt1);
  printf("hull time:  %s\n\n", buf);
  fflush(stdout);  

  //start the rendering 
  /* initialize GLUT  */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);

  /* register callback functions */
  glutDisplayFunc(display); 
  glutKeyboardFunc(keypress);

  /* init GL */
  /* set background color black*/
  glClearColor(0, 0, 0, 0);   
  
  /* give control to event handler */
  glutMainLoop();
  return 0;
}


/* ****************************** */
/* This is the function that renders the window. We registered this
   function as the "displayFunc". It will be called by GL everytime
   the window needs to be rendered.
 */
void display(void) {

  glClear(GL_COLOR_BUFFER_BIT);
  //clear all modeling transformations
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity(); 


  /* The default GL window is [-1,1]x[-1,1]x[-1,1] with the origin in
     the center. The camera is at (0,0,0) looking down negative
     z-axis.  

     The points are in the range [0, WINSIZE] x [0, WINSIZE] so they
     need to be mapped to [-1,1]x [-1,1] */
  
  //then scale the points to [0,2]x[0,2]
  glScalef(2.0/WINDOWSIZE, 2.0/WINDOWSIZE, 1.0);  
  //first translate the points to [-WINDOWSIZE/2, WINDOWSIZE/2]

  glTranslatef(-WINDOWSIZE/2, -WINDOWSIZE/2, 0); 
 
  draw_points(points);
  draw_hull(hull); 

  /* execute the drawing commands */
  glFlush();
}


/* ****************************** */
/* draw the points. each point is drawn as a small square
*/
void draw_points(vector<point2d> points){

  const int R= 1;
  //draw polygon filled or line 
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  //set drawing color 
  glColor3fv(yellow);   
  
  for (int i=0; i< points.size(); i++) {
    //draw a small square centered at (points[i].x, points[i].y)
    glBegin(GL_POLYGON);
    glVertex2f(points[i].x -R,points[i].y-R);
    glVertex2f(points[i].x +R,points[i].y-R);
    glVertex2f(points[i].x +R,points[i].y+R);
    glVertex2f(points[i].x -R,points[i].y+R);
    glEnd();
  }
} //draw_points 





/* ****************************** */
/* Draw the hull; the points on the hull are expected to be in
   boundary order (either ccw or cw) or else it will look
   zig-zaagged. To render the hull we'll draw lines between
   consecutive points */
void draw_hull(vector<point2d> hull){

  //set color 
  glColor3fv(red);   //this should be a constant
  
  if (hull.size() >0) {
    int i; 
    for (i=0; i< hull.size()-1; i++) {
      
      //draw a line from  i to i+1
      glBegin(GL_LINES);
      glVertex2f(hull[i].x, hull[i].y); 
      glVertex2f(hull[i+1].x, hull[i+1].y); 
      glEnd();
    }
    
    //draw a line from the last point to the first point
    i =  hull.size()-1; 
    glBegin(GL_LINES);
    glVertex2f(hull[i].x, hull[i].y); 
    glVertex2f(hull[0].x, hull[0].y); 
    glEnd();
  }//if (hull not empty)
}



/* ****************************** */
/* Handler for key presses. called whenever a key is spressed */
void keypress(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    exit(0);
    break;

  case 'i':
    //when the user presses 'i', we want to re-initialize the points and
    //recompute the hull
    POINT_INIT_MODE = (POINT_INIT_MODE+1) % NB_INIT_CHOICES; 

    switch (POINT_INIT_MODE) {
    case 0: 
      initialize_points_circle(points, NPOINTS); 
      break; 
    case 1: 
      initialize_points_cross(points, NPOINTS); 
      break; 
    case 2: 
      initialize_points_horizontal_line(points, NPOINTS); 
      break; 
    case 3: 
      initialize_points_random(points, NPOINTS); 
      break; 
    case 4: 
      initialize_points_heart(points, NPOINTS);
      break;
    case 5: 
      initializer_square(points, NPOINTS);
      break;
    case 6:
      initialize_points_2(points, NPOINTS);
      break;
    case 7: 
      initialize_points_thin_cross(points, NPOINTS);
      break;
    case 8:
      initialize_points_stripes(points, NPOINTS);
      break;
    case 9:
      initialize_points_spiral(points, NPOINTS);
      break;
    case 10:
      initialize_points_spiral(points, NPOINTS);
      break;
    case 11: 
      initialize_points_wave(points, NPOINTS);
      break;
    case 12: 
      initialize_points_hardcoded_triangle(points, NPOINTS);
      break;
    case 13: 
      initialize_points_two_vertical(points, NPOINTS);
      break;
    case 14: 
      initialize_points_vertical_line(points, NPOINTS);
      break;

    } //switch 
    //we changed the points, so we need to recompute the hull
    graham_scan(points, hull); 

    //we changed stuff, so we need to tell GL to redraw
    glutPostRedisplay();

  } //switch (key)

}//keypress


