# hull2d-startup


2d convex hull startup code.  

Should compile as is.

Team members Zaynab Azzouzi, Alex Washburn

In this project we implement the graham scan function, and helper functoins signed_area2D(), collinear(), left_strictly(), and left_on(). We also created a comparator, compare_angles(), for sorting and initializers to test our data on. 3 of the initialziers in our code are from our classmates and we indicate which they are. 

In graham scan we build our hull. We start off by looping through the vector pts and finding the point with the lowest y value to set as our global variable p0. If there are multiple values tied for lowest y value we take the one with the larget x value.
This point is guaranteed to be on the hull because it is extreme. 
After setting p0 we delete that point from pts so it isn't considered during sorting. We decided to use qsort for sorting and created a comparator to feed it. In our compare_angles() function we take in 2 points and determine which one would be sorted before the other. We compare their angles using horiontal line through p0 as the base. Whichever point had a smaller angle would be sorted first. If the points were collinear with p0 (this means the 2 points had the same angle measured from p0) then the point that was closer to p0 would be sorted first. 

An array pts_array was created to feed into qsort, along with the comparator. After the pts was sorted, p0 and pts[0] were pushed onto the hull. Then we enter a while loop in which we inspect the points in pts. If the current point is strictly to the left of the line segment between the 2 points at top of the hull then it is pushed onto the hull. If not then we pop the top point of the hull and repeat the process until the hull is completed. If the hull ever contains p0 we simply add the current point and continue. 

We created and copied and pasted several initializers (functions that create, draw and display points on the screen) in viewhull.cpp. Our main functoin takes in an input n from the user that tells the initializer how many points to make, runs the initialier, runs graham scan, and then draws the hull created by graham scan. 
 
