# hull2d-startup


1. Lab group: Zaynab Azzouzi, Alex Washburn

2. Brief description of the project: In this project, we implemented the Graham Scan algorithm to 
compute the convex hull of a set of given points. The initialization of the points was done in the
viewhull.cpp file, and the computation of the set of points contained in the convex hull was done in
the geom.cpp file. 

Briefly, the way we decided to implement the graham scan was to first find the lowest point amoung 
all of the points (rightmost point if there was a tie), and we called this point p0. We then sorted
the points by their counter-clockwise angle with respect to p0 by implementing a comparator and 
using a built-in method (qsort()) to sort based on the comparator. Some caveats here included 
the issue of points that created the same angle with p0 (i.e a set of points that were collinear 
with each other and also p0). To handle this case, we simply ordered the points from closest to 
farthest from p0 in the case of a tie (using the magnitude of the Manhattan distance as a metric). 

Once all of our points were sorted, we then traversed the points in counter-clockwise order 
to build up a chain of points that are on the convex hull. This was done by comparing a potential 
point to be added to the convex hull to the LINE connects the most recently added two points in our
current chain of points in the convex hull: if the potential point is to the left of the line, 
then this point can be added to the convex hull, and we push it to the chain. However, if the 
potential point is to the right of the line segment, we need to pop off the last point in the 
current chain of points in the convex hull and then try our next point in sorted order and see 
if it can be added to the convex hull. Note that a vertex could theoretically create a series
of repeated pops off of our current chain of points in the convex hull.

One issue that arises is that of colinearity: however, due to the way that the points were sorted, 
the algorithm described above correctly finds the convex hull even with collinear points.

Lastly, we created and copied and pasted several initializers (functions that create, draw and 
display points on the screen) in viewhull.cpp. Our main functoin takes in an input n from the user 
that tells the initializer how many points to make, runs the initialier, runs graham scan, and then 
draws the hull created by graham scan. 

3. How to run the project: In order to run the project, one should type "./hull 2d n", where n is the 
number of points one intends to generate. In the main method, specify which point initialization
configuration you would like to use first. From here, recompute the set of points and find the 
convex hull using Graham Scan for all the other point initialization configurations, simply 
press the key "i" repeatedly. This will re-initialize and compute the convex hull for the point 
configurations: [TODO] in order. Note: for a given set of initialized poitns, the points in the
convex hull will be printed out in the output console. 
 
