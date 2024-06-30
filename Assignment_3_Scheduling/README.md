
BLG 336E - Analysis of Algorithms II

Assignment 3
Overview

This project implements two main algorithms: Weighted Interval Scheduling and Knapsack. The program schedules rooms with the highest priority and selects items maximizing value within a given budget.
Problem Description

    Weighted Interval Scheduling: Finds the optimal schedule of room usage across different floors based on priority and time intervals.
    Knapsack Problem: Selects items that maximize value within a specified budget.

Code Structure

    Structures:
        TimeIntervals: Represents start and end times in minutes.
        Priority: Holds room, floor, and priority level.
        Schedule: Contains scheduling details, including time intervals and weights.
        Item: Represents an item with name, price, and value.

    Functions:
        binary_search: Finds the last non-conflicting schedule.
        weighted_interval_scheduling: Computes the optimal schedule for each floor.
        knapsack: Selects the most valuable items within a budget.

Input Files

The program requires the following files in the ./inputs/case_<number>/ directory:

    room_time_intervals.txt:
        Format: floor room start_time end_time
        Example:
    ˙˙˙
    Floor_1 Room_101 08:00 10:00
    Floor_1 Room_102 10:00 12:00
    ˙˙˙
priority.txt:

    Format: floor room priority
    Example:
    ˙˙˙
    Floor_1 Room_101 5
    Floor_1 Room_102 3
    ˙˙˙
items.txt:

    Format: name price value
    Example:

    ˙˙˙

        ItemA 1000 10.5
        ItemB 2000 20.0
    ˙˙˙
Compilation

To compile the program, use the following command:

˙˙˙

g++ -o scheduling scheduling.cpp -std=c++11
˙˙˙
Execution

Run the program with the case number as an argument:

˙˙˙

./scheduling <case_number>
˙˙˙
Example:

˙˙˙

./scheduling 1
˙˙˙
Output Format

The program outputs the optimal room scheduling and the best use of budget:

    Room Scheduling:

˙˙˙

Floor_1 --> Priority Gain: 15
Floor_1    Room_101    08:00    10:00
Floor_1    Room_102    10:00    12:00
˙˙˙
Best Use of Budget:

˙˙˙

    Best Use of Budget
    Total Value: 30.5
    ItemA
    ItemB
˙˙˙
Algorithms

    Weighted Interval Scheduling:
        Uses dynamic programming to select non-overlapping intervals with the highest total priority.
        Sorts schedules by end times, using a binary search to find compatible intervals.

    Knapsack Problem:
        Utilizes a dynamic programming approach to maximize item value within a budget.
        Sorts items by value-to-price ratio and selects optimal items based on budget constraints.

Libraries Used

    <iostream>: Standard input/output.
    <fstream>: File handling.
    <vector>: Dynamic arrays.
    <string>: String manipulation.
    <algorithm>: Sorting and searching algorithms.
    <regex>: Regular expressions for parsing input.
    <set>: Unique element containers.
    <map>: Key-value pairs.
    <iomanip>: Input/output formatting.

Conclusion

This program demonstrates the application of dynamic programming to solve real-world scheduling and resource allocation problems. The results include optimal schedules for room usage and a selection of items that maximize budget utilization.