Divide and Conquer Algorithm - Closest Pair of Points
BLG 336E - Analysis of Algorithms II

Assignment 2
Mehmet Utku Colak
504231528
Overview

This assignment involves implementing the divide and conquer approach to solve the "Closest Pair of Points" problem in C++. The goal is to efficiently find the closest pair of points in a two-dimensional space from a given set of points.
Problem Description

The "Closest Pair of Points" problem requires finding two points in a plane that are closer together than any other pair of points. This implementation uses a divide and conquer strategy to improve efficiency over the brute force approach.
Algorithm
Steps:

    Divide: Split the set of points into two halves.
    Conquer: Recursively find the closest pair of points in each half.
    Combine: Merge the results by checking points in a strip across the dividing line to ensure no closer pairs exist.

Brute Force Base Case

For small sets of points (≤3000), the algorithm switches to a brute force method to ensure optimal performance.
Code Structure

    Point Structure: Represents a point in 2D space with x and y coordinates.
    Distance Calculation: Computes the Euclidean distance between two points.
    Sorting Functions: Used to sort points based on x or y coordinates.
    Brute Force Method: Finds the closest pair of points by examining each pair.
    Divide and Conquer Method: Recursively finds the closest pair of points by dividing the problem and combining results.
    Closest Pair Order Function: Iteratively finds and removes the closest pairs, storing them for output.
    File Reading Function: Reads point coordinates from a file and returns them as a vector of Point objects.
    Main Function: Handles file input and initiates the closest pair search.

Usage
Compilation

To compile the program, use the following command in your terminal:

bash

g++ -o closest_pair closest_pair.cpp -std=c++11

Running the Program

Execute the program with the name of the input file containing point coordinates:

bash

./closest_pair points.txt

Input File Format

The input file should contain pairs of x and y coordinates, one pair per line:

python

1.0 2.0
3.0 4.0
5.0 6.0
...

Output

The program prints pairs of points that are closest together in the format:

python

Pair 1: x1, y1 - x2, y2
Pair 2: x3, y3 - x4, y4
...
Unconnected x, y  // If there's an unconnected point

Performance

The divide and conquer approach significantly reduces the time complexity to O(nlog⁡n)O(nlogn) compared to the brute force approach with O(n2)O(n2). Timing measurements can be inserted to evaluate performance but are commented out in the provided code.
Libraries Used

    <iostream>: For input and output operations.
    <cmath>: For mathematical functions like sqrt().
    <vector>: To store points.
    <algorithm>: For sorting functions.
    <limits>: To use the maximum value for distance comparisons.
    <fstream>: For file handling.
    <chrono>: To measure execution time.

Conclusion

This program efficiently finds the closest pairs of points using a divide and conquer strategy, demonstrating the power of this approach in reducing computational complexity for large datasets.