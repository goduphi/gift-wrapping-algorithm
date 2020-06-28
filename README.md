# Gift wrapping-algorithm
The gift wrapping algorithm for computing the convex hull was a part of my Honors Project for CSE2320 - Algorithms and Data Structures

### Resource used:
Introduction to Algorithms - Third Edition  
Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein
  
### File descriptions
- rand.c - This file containes all the source code for generating random coordinates.
- convex_hull_jarvis_march.c - This file containes all the source code for the gift wrapping algorithm.
- all_points.txt - A list of the all the points from random.txt (A separate file created to make it easier to plot in excel).
- outerpoints.txt - A list of all the points that lie on the convex hull
- convex_hull_plot.xlsx - A sample plot of the output

### Compilation instructions:
Random coordinate generator: ```gcc -o rand rand.c -g```  
Convex hull Jarvis March: ```gcc -o convex_hull_jarvis_march convex_hull_jarvis_march.c -g```  

Note: The -g flag is optional. I only used it for debugging purposes.  

### Usage
Random coordinate generator: `./rand <Size of data set, Max: 100> <Range of data set, Max: 1000>`   
Convex hull Jarvis March: `./convex_hull_jarvis_march < <Outputfile.txt from rand program>`
