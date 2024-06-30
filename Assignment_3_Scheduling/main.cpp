/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 3
 * <Name & Surname>
 * <Student ID>
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
/* YOU CAN INCLUDE ANY OTHER NECESSARY LIBRARIES */
#include <map>
#include <set>
#include <string>
#include <iomanip>
/* YOU CAN DEFINE EXTRA FUNCTIONS AND MODIFY THE CODE TEMPLATE */

/* YOU HAVE TO CONSIDER THE OUTPUT FORMAT TO TEST YOUR CODE WITH CALICO */

using namespace std;

#include <chrono>

struct TimeIntervals {
  int start_time_in_minutes;
  int end_time_in_minutes;
};

struct Priority {
  int room;
  int floor;
  int priority;
};
struct Schedule {
  int floor;
  int room;
  TimeIntervals interval;
  int weight;
};

struct Item {

  // YOUR CODE HERE
  string name;
  int price;
  float value;
};
bool class_compare(const Schedule &a, const Schedule &b) {
  if (a.interval.start_time_in_minutes == b.interval.start_time_in_minutes &&
      a.interval.end_time_in_minutes == b.interval.end_time_in_minutes) {
    return a.weight > b.weight;
  }
  return a.interval.end_time_in_minutes < b.interval.end_time_in_minutes;
}

int binary_search(const vector<Schedule> &schedules, int index) {
  int low = 0;
  int high = index - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (schedules[mid].interval.end_time_in_minutes <=
        schedules[index].interval.start_time_in_minutes) {
      if (schedules[mid + 1].interval.end_time_in_minutes <=
          schedules[index].interval.start_time_in_minutes) {
        low = mid + 1;
      } else {
        return mid;
      }
    } else {
      high = mid - 1;
    }
  }
  return -1;
}
// function to find the best schedule for each floor
vector<Schedule> weighted_interval_scheduling(vector<Schedule> &schedules) {
    sort(schedules.begin(), schedules.end(), class_compare);

    int n = schedules.size();
    vector<int> dp(n); // dp[i] will store the maximum weight of the interval schedule ending at i
    vector<int> p(n); // p[i] will store the index of the last non-conflicting schedule before i

    // Initialize the first schedule
    dp[0] = schedules[0].weight;
    p[0] = -1; // No previous schedule for the first one

    // Fill the dp and p arrays
    for (int i = 1; i < n; ++i) {
        int include_weight = schedules[i].weight;
        int l = binary_search(schedules, i);
        if (l != -1) {
            include_weight += dp[l];
        }
        dp[i] = max(include_weight, dp[i - 1]);
        if (include_weight > dp[i - 1]) {
            p[i] = l;
        } else {
            p[i] = p[i - 1];
        }
    }

    // Reconstruct the optimal schedule from the dp and p arrays
    vector<Schedule> optimal_schedules;
    int i = n - 1;
    while (i >= 0) {
        if (dp[i] == dp[i - 1]) {
            --i;
        } else {
            optimal_schedules.push_back(schedules[i]);
            i = p[i];
        }
    }

    reverse(optimal_schedules.begin(), optimal_schedules.end());
    return optimal_schedules;
}

// *** END ***

/* START: KNAPSACK (for items) */

// Function to select the most valuable items that can be purchased with a
// certain budget
vector<Item> knapsack(const vector<Item> &Items, int budget) {

  // Sort the items by their value in descending order
vector<Item> sorted_items = Items;
sort(sorted_items.begin(), sorted_items.end(),
         [](const Item &a, const Item &b) { return a.value > b.value; });

// Initialize the dynamic programming table
vector<vector<float>> dp(Items.size() + 1, vector<float>(budget + 1, 0));

// Fill in the dynamic programming table
for (int i = 1; i <= static_cast<int>(Items.size()); i++) {
    for (int j = 1; j <= budget; j++) {
        if (sorted_items[i - 1].price <= j) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - sorted_items[i - 1].price] +
                                                                             sorted_items[i - 1].value);
        } else {
            dp[i][j] = dp[i - 1][j];
        }
    }
}

// Backtrack to find the selected items
vector<Item> selected_items;
int i = Items.size();
int j = budget;
while (i > 0 && j > 0) {
    if (dp[i][j] != dp[i - 1][j]) {
        selected_items.push_back(sorted_items[i - 1]);
        j -= sorted_items[i - 1].price;
    }
    i--;
}

return selected_items;
}

// *** END ***

int main(int argc, char *argv[]) {
  string case_no = argv[1];
  string case_name = "case_" + case_no;
  string path = "./inputs/" + case_name;
  vector<Schedule> schedules;
  int total_budget = 200000;

  // YOUR CODE HERE
  ifstream file(path + "/room_time_intervals.txt");
  if (!file.is_open()) {
    cout << "Failed to open file." << endl;
    return 1;
  }
  set<int> floor_count;
  vector<TimeIntervals> intervals;
  string line;
  getline(file, line);
  regex number_regex(R"(\d+)");
  smatch number_match;
  while (getline(file, line)) {
    stringstream ss(line);
    // TimeIntervals interval;
    Schedule schedule;
    auto &interval = schedule.interval;
    string floor, room, start_time, end_time;
    ss >> floor >> room >> start_time >> end_time;
    regex_search(floor, number_match, number_regex);
    int floor_number = stoi(number_match.str());
    floor_count.insert(floor_number);
    schedule.floor = floor_number;
    // Extract the numeric part of the room name
    regex_search(room, number_match, number_regex);
    schedule.room = stoi(number_match.str());

    // Extract the numeric part of the start time
    regex time_regex(R"(\d+:\d+)");
    smatch start_time_match;
    regex_search(start_time, start_time_match, time_regex);
    string start_time_str = start_time_match.str();
    int colon_pos = start_time_str.find(":");
    int hours = stoi(start_time_str.substr(0, colon_pos));
    int minutes = stoi(start_time_str.substr(colon_pos + 1));
    interval.start_time_in_minutes = hours * 60 + minutes;

    // Extract the numeric part of the end time
    smatch end_time_match;
    regex_search(end_time, end_time_match, time_regex);
    string end_time_str = end_time_match.str();
    colon_pos = end_time_str.find(":");
    hours = stoi(end_time_str.substr(0, colon_pos));
    minutes = stoi(end_time_str.substr(colon_pos + 1));
    interval.end_time_in_minutes = hours * 60 + minutes;

    schedules.push_back(schedule);
  }

  file.close();

  ifstream priority_file(path + "/priority.txt");
  if (!priority_file.is_open()) {
    cout << "Failed to open priority file." << endl;
    return 1;
  }

  vector<Priority> priorities;
  getline(priority_file, line);
  while (getline(priority_file, line)) {
    stringstream ss(line);
    Priority priority;
    string floor_name, room_name, priority_value;
    ss >> floor_name >> room_name >> priority_value;

    // Extract the numeric part of the floor name
    regex floor_regex(R"(\d+)");
    smatch floor_match;
    regex_search(floor_name, floor_match, floor_regex);
    priority.floor = stoi(floor_match.str());

    // Extract the numeric part of the room name
    regex room_regex(R"(\d+)");
    smatch room_match;
    regex_search(room_name, room_match, room_regex);
    priority.room = stoi(room_match.str());

    priority.priority = stoi(priority_value);

    priorities.push_back(priority);
  }

  priority_file.close();
  vector<Item> items;
  float total_value = 0;
    ifstream item_file(path + "/items.txt");
    if (!item_file.is_open()) {
        cout << "Failed to open priority file." << endl;
        return 1;
    }
    getline(item_file, line);
    while (getline(item_file, line)) {
        stringstream ss(line);
        Item item;
        string name, price, value;
        ss >> name >> price >> value;
        item.name = name;
        item.price = stoi(price);
        item.value = stof(value);
        items.push_back(item);
    }
  vector<Schedule> updated_schedules;
  for (auto &schedule : schedules) {

    for (const auto &priority : priorities) {
      if (priority.floor == schedule.floor && priority.room == schedule.room) {
        schedule.weight = priority.priority;
        break;
      }
    }

    updated_schedules.push_back(schedule);
  }
  //{floor = 1, interval = {room = 1, start_time = 10, end_time = 13}, weight =
  // 70}
  vector<Schedule> floor_schedules[floor_count.size()];
  for (const auto &schedule : updated_schedules) {
    floor_schedules[schedule.floor - 1].push_back(schedule);
  }

  for (int i = 0; i < static_cast<int>(floor_count.size()); i++) {
    auto total_weight = 0;
    const auto schedule = weighted_interval_scheduling(floor_schedules[i]);
    for (const auto &auto_schedule : schedule) {
      total_weight += auto_schedule.weight;
    }
    cout << "Floor_" << i + 1 << " --> " << "Priority Gain: " << total_weight
       << endl;
    for (const auto &auto_schedule : schedule) {
      std::cout << "Floor_" << auto_schedule.floor << "\t" << "Room_" << auto_schedule.room << "\t" << setfill('0') << setw(2)  << auto_schedule.interval.start_time_in_minutes / 60 << ":" << setw(2) <<  auto_schedule.interval.start_time_in_minutes % 60 <<  "\t"
       << setw(2) << auto_schedule.interval.end_time_in_minutes / 60 << ":" << setw(2) << auto_schedule.interval.end_time_in_minutes % 60 << std::endl;
    }
    cout << endl;
  }
  auto selected_items = knapsack(items, total_budget);
    cout << "Best Use of Budget" << endl;
    for( const auto &item : selected_items ) {
        total_value += item.value;
    }
    cout << "Total Value: " << total_value << endl;
    for( const auto &item : selected_items ) {
        cout << item.name << endl;
    }
    
  return 0;
}