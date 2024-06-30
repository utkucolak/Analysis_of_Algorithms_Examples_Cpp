/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 2
 * Mehmet Utku Colak
 * 504231528
*/


#include <iostream>   // For input/output
#include <cmath>      // For distance calculations
#include <vector>     // For vector operations
#include <algorithm>  // For sorting operations
#include <limits>     // For min(), max() functions
#include <fstream>    // To read/write files
#include <chrono>     // For time measurement

//(These libraries are sufficient for this assignment.)

using namespace std;

// Structure to represent a point in 2D space
struct Point {
    double x, y;
};

// Helper function to calculate distance between two points
double distance(Point p1, Point p2) {

    auto distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    return distance;

}

// Helper function to compare points based on x-coordinate, can use this for sorting.
bool compareX(Point p1, Point p2) {

    return p1.x < p2.x;

}

// Helper function to compare points based on y-coordinate, can use this for sorting.
bool compareY(Point p1, Point p2) {

    return p1.y < p2.y;

}

// Function to find the closest pair of points using brute force.
pair<Point, Point> bruteForceClosestPair(vector<Point>& points, int start, int end) {

    pair<Point, Point> closestPair;
    double minDistance = numeric_limits<double>::max();

    for (int i = start; i < end; i++) {
        for (int j = i + 1; j < end; j++) {
            double dist = distance(points[i], points[j]);
            if (dist < minDistance) {
                minDistance = dist;
                closestPair = make_pair(points[i], points[j]);
            }
        }
    }

    return closestPair;

}
// The main objective of the assignment. This is the function to find the closest pair of points recursively using divide and conquer.
pair<Point, Point> closestPair(vector<Point>& points, int start, int end) {
    auto n = end - start;
    if (n <= 3000) {
        return bruteForceClosestPair(points, start, end);
    }
    auto mid = (start + end) / 2;
    auto leftPair = closestPair(points, start, mid);
    auto rightPair = closestPair(points, mid, end);
    auto minPair = (distance(leftPair.first, leftPair.second) < distance(rightPair.first, rightPair.second)) ? leftPair : rightPair;
    vector<Point> strip;
    for (int i = start; i < end; i++) {
        if (abs(points[i].x - points[mid].x) < distance(minPair.first, minPair.second)) {
            strip.push_back(points[i]);
        }
    }
    sort(strip.begin(), strip.end(), compareY);
    for (size_t i = 0; i < strip.size(); i++) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < distance(minPair.first, minPair.second); j++) {
            auto dist = distance(strip[i], strip[j]);
            if (dist < distance(minPair.first, minPair.second)) {

                    minPair = make_pair(strip[i], strip[j]);

        }
        }
    }
    return minPair;
}


// Function to remove a pair of points from the point vector. Returns the newly formed vector.
vector<Point> removePairFromVector(vector<Point>& point_vector, pair<Point,Point> point_pair) {
    for (int i = 0; i < static_cast<int>(point_vector.size()); i++) {
        if (point_vector[i].x == point_pair.first.x && point_vector[i].y == point_pair.first.y) {
            point_vector.erase(point_vector.begin() + i);
        }
        
    }
    for (int i = 0; i < static_cast<int>(point_vector.size()); i++){
        if (point_vector[i].x == point_pair.second.x && point_vector[i].y == point_pair.second.y) {
                point_vector.erase(point_vector.begin() + i);
            }
    }
    return point_vector;

}

// This function should wrap up the entire algorithm. It should:
//    1- Find the closest pair
//    2- Add the pair to the "pairs" vector
//    3- Remove the paired result from the map
// at each iteration.
// Then it should set "unconnected" variable as the final, unconnected city (if it exists).
void findClosestPairOrder(vector<Point> points) {
    //auto start_time = chrono::high_resolution_clock::now();
    vector<pair<Point,Point>> pairs; //add your pairs to this vector
    Point unconnected = {-1,-1}; //set this as the unconnected point if it exists, leave as is otherwise.
    sort(points.begin(), points.end(), compareX);
    while (points.size() >= 2) {
        auto start = 0;
        auto end = static_cast<int>(points.size());
        auto closest = closestPair(points, start, end);
        pairs.push_back(closest);
        points = removePairFromVector(points, closest);
    }

    if (points.size() == 1) {
        unconnected = points[0];
    }
    for(size_t i = 0; i < pairs.size(); i++){
        
        if (pairs[i].first.y > pairs[i].second.y) {
            swap(pairs[i].first, pairs[i].second);
        }
        else if (pairs[i].first.y == pairs[i].second.y && pairs[i].first.x > pairs[i].second.x) {
            swap(pairs[i].first, pairs[i].second);
        }
    }
    //auto end_time = chrono::high_resolution_clock::now();
    //auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    //cout << "Total time taken: " << duration.count() << " microseconds" << endl;
    //before printing, please make sure that within each pair, the city with the smaller y coordinate is printed first...
    //...if the y coordinates are the same, print the city with the smaller x coordinate first.

    //This part prints the output, don't modify.    
    for(size_t i = 0; i < pairs.size(); i++){
        cout << "Pair " << i+1 << ": " << pairs[i].first.x << ", " << pairs[i].first.y << " - " << pairs[i].second.x << ", " << pairs[i].second.y << endl;
    }
    if (unconnected.x != -1){
        cout << "Unconnected " << unconnected.x << ", " << unconnected.y;
    }


}

//Read the coordinates from the file and convert them to a vector. Return the vector as a "vector<Point>"
vector<Point> readCoordinatesFromFile(const string& filename) {
    vector<Point> points;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File not found!" << endl;
        return points;
    }

    else{
        double x, y;
        while (file >> x >> y) {
            points.push_back(Point{x, y});
        }
        
    }

    return points;
}

// Main function. Ideally, you don't need to modify this.
int main(int argc, char* argv[]) {
    vector<Point> points = readCoordinatesFromFile(argv[1]);
    findClosestPairOrder(points);
    return 0;
}
