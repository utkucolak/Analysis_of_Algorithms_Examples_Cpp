/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 1
 * <Name & Surname>
 * <Student ID>
*/

/* * * * * * * * * * * * * * * * * *
 * DO NOT MODIFY UNLESS REQUESTED  *
* * * * * * * * * * * * * * * * * */

#include <iostream>         
#include <vector>
#include <fstream>
#include <sstream>       
#include <stack>
#include <queue>
#include <chrono>       // For time measurement

/* INCLUDE ANY OTHER NECESSARY LIBRARIES HERE */
/* START YOUR CODE HERE */
#include <algorithm>
/* END YOUR CODE HERE */

using namespace std;
using namespace std::chrono;

/* USE HERE IF YOU NEED TO DEFINE EXTRA FUNCTIONS */
/* START YOUR CODE HERE */


/* END YOUR CODE HERE */

/**
 * Perform Depth-First Search (DFS) traversal on a map.
 * 
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the DFS traversal.
 * @param col The starting column index for the DFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the DFS traversal.
 */
int dfs(vector<vector<int>>& map, int row, int col, int resource) {

    /* START YOUR CODE HERE */
    // Check if the current position is out of bounds or the resource value is not the one we are searching for


    if (row < 0 || static_cast<long unsigned int>(row) >= map.size() || col < 0 || static_cast<long unsigned int>(col) >= map[0].size() || map[row][col] != resource) {
        return 0;
    }


    // Mark the current position as visited
    map[row][col] = -1;

    // Initialize the size of the colony
    int colonySize = 1;

    // Perform DFS traversal on the neighboring cells
    colonySize += dfs(map, (row - 1 + map.size()) % map.size(), col, resource); // Up
    colonySize += dfs(map, (row + 1) % map.size(), col, resource); // Down
    colonySize += dfs(map, row, (col - 1 + map[0].size()) % map[0].size(), resource); // Left
    colonySize += dfs(map, row, (col + 1) % map[0].size(), resource); // Right


    // Return the size of the colony
    return colonySize;
    }    
    
    /* END YOUR CODE HERE */




/**
 * Perform Breadth-First Search (BFS) traversal on a map.
 * 
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the BFS traversal.
 * @param col The starting column index for the BFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the BFS traversal.
 */
int bfs(vector<vector<int>>& map, int row, int col, int resource) {
    
    /* START YOUR CODE HERE */
    // Create a queue for BFS traversal
    queue<pair<int, int>> q;

    // Check if the starting position is out of bounds or the resource value is not the one we are searching for
    if (row < 0 || static_cast<long unsigned int>(row) >= map.size() || col < 0 || static_cast<long unsigned int>(col) >= map[0].size() || map[row][col] != resource) {
        return 0;
    }

    // Mark the starting position as visited
    map[row][col] = -1;

    // Initialize the size of the colony
    int colonySize = 1;

    // Enqueue the starting position
    q.push({row, col});

    // Perform BFS traversal
    while (!q.empty()) {
        // Dequeue the front position
        pair<int, int> current = q.front();
        q.pop();

        // Get the row and column indices of the current position
        int r = current.first;
        int c = current.second;
        // Check the neighboring cells
        if (map[(r - 1 + map.size()) % map.size()][c] == resource) { // Up
            map[(r - 1 + map.size()) % map.size()][c] = -1; // Mark as visited
            colonySize++;
            q.push({(r - 1 + map.size()) % map.size(), c});
        }
        if (map[(r + 1) % map.size()][c] == resource) { // Down
            map[(r + 1) % map.size()][c] = -1; // Mark as visited
            colonySize++;
            q.push({(r + 1) % map.size(), c});
        }
        if (map[r][(c - 1 + map[0].size()) % map[0].size()] == resource) { // Left
            map[r][(c - 1 + map[0].size()) % map[0].size()] = -1; // Mark as visited
            colonySize++;
            q.push({r, (c - 1 + map[0].size()) % map[0].size()});
        }
        if (map[r][(c + 1) % map[0].size()] == resource) { // Right
            map[r][(c + 1) % map[0].size()] = -1; // Mark as visited
            colonySize++;
            q.push({r, (c + 1) % map[0].size()});
        }
    }

    // Return the size of the colony
    return colonySize;

    /* END YOUR CODE HERE */

}

/**
 * Finds the top-k largest colonies in a given map.
 *
 * @param map The map represented as a 2D vector of integers.
 * @param useDFS A boolean flag indicating whether to use Depth-First Search (DFS) or Breadth-First Search (BFS) algorithm.
 * @param k The number of top colonies to find.
 * @return A vector of pairs representing the size and resource type of the top-k largest colonies.
 */
vector<pair<int, int>> top_k_largest_colonies(vector<vector<int>>& map, bool useDFS, unsigned int k) {

    auto start = high_resolution_clock::now();      // Start measuring time
    
    /* START YOUR CODE HERE */
    auto my_map = map;
    // Initialize a vector to store the size and resource type of the colonies
    vector<pair<int, int>> colonies;

    // Iterate over each cell in the map
    for (int i = 0; static_cast<long unsigned int>(i) < map.size(); i++) {
        for (int j = 0; static_cast<long unsigned int>(j) < map[0].size(); j++) {
            // Check if the cell is unvisited and contains a resource
            if (map[i][j] > 0) {
                // Perform DFS or BFS based on the flag useDFS
                int colonySize;
                if (useDFS) {
                    colonySize = dfs(map, i, j, map[i][j]);
                } else {
                    colonySize = bfs(map, i, j, map[i][j]);
                }
                // Add the colony size and resource type to the vector
                colonies.push_back({colonySize, my_map[i][j]});
            }
        }
    }

    // Sort the colonies in descending order based on their size
    std::sort(colonies.begin(), colonies.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b){
        if (a.first == b.first) {
            // In case of equality on the first element, sort by the second in descending order
            return b.second > a.second;
        }
        // Otherwise, sort by the first element in ascending order
        return a.first > b.first;
    }
    );
    auto end = high_resolution_clock::now();
    // Calculate the time elapsed in milliseconds
    auto duration = duration_cast<microseconds>(end - start);
    
    int timelapse = duration.count();
    std::cout << timelapse << "\n";
    return std::vector<std::pair<int, int>>(colonies.begin(), colonies.begin() + std::min(k, static_cast<unsigned int>(colonies.size())));

    /* END YOUR CODE HERE */

}

// Main function
int main(int argc, char* argv[]) {

    // Check the command line arguments
    if (argc != 4) {

        // It should be: <1 or 0> <k> <filename.txt>
        cerr << "Usage: " << argv[0] << " <1 or 0> <k> <filename.txt>" << endl;
        return 1;
    }

    // Get the arguments
    bool useDFS = (atoi(argv[1]) == 1);
    int k = atoi(argv[2]);

    // Read the map from the text file
    string filename = argv[3];
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    vector<vector<int>> sector_map;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<int> row;
        int num;
        while (iss >> num) {
            row.push_back(num);
        }
        sector_map.push_back(row);
    }
    file.close();   

    // Find the largest colony
    vector<pair<int, int>> result = top_k_largest_colonies(sector_map, useDFS, k);

    // Print the result
    std::cout << "Algorithm: " << (useDFS ? "DFS" : "BFS") << endl;
    std::cout << "Map: " << filename << endl;

    // If no colonies are found
    if (result.empty()) {
        std::cout << "No colonies found." << endl;
        return 0;
    }

    // Print the top-k colonies
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "Colony " << i + 1 << ": Size = " << result[i].first << ", Resource Type = " << result[i].second << endl;
    }

    return 0;
}