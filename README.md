# gift-wrapping-algorithm
Gift wrapping algorithm for computing the convex hull as part of my Honors Project for CSE2320 - Algorithms and Data Structures

rand.c - generates random coordinates
       - compile using: gcc -o rand rand.c -g
       - run using: rand 100 (size of data set) 1000 (range of data set)

convex_hull_jarvis_march.c - computes the convex hull
        - compile using: gcc -o convex_hull_jarvis_march convex_hull_jarvis_march.c -g
        - run using: convex_hull_jarvis_march < random.txt (output file from the rand program)
        
all_points.txt - a list of the all the points from random.txt (separate file create to make it easier to plot in excel)

outerpoints.txt - a list of all the points that lie on the convex hull

convex_hull_plot.xlsx - a sample plot of the output
