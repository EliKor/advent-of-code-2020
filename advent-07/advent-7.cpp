#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;

string parse_word(string& line, int& i) {
    string word;
    while (i < line.size() && line[i] != ' ') {
        word.push_back(line[i]);
        i++;
    }
    return word;
}

string parse_bag_color(string& line, int& i) {
    string bag_color = "";
    bag_color += parse_word(line, i);
    i++;
    bag_color += parse_word(line, i);
    return bag_color;
}

void parse_neighbors(string& line, int& i, unordered_map<string, vector<pair<string, int>>>& map, string& parent) {
    string ending = ",";
    while (ending[ending.size()-1] != '.') {
        string count = parse_word(line, i);
        if (count == "no") {
            return;
        }
        i++;
        string bag_color = parse_bag_color(line, i);
        // map[bag_color].insert(parent);
        map[parent].push_back({bag_color, stoi(count)});
        i++;
        ending = parse_word(line, i);
        i++;
    }
}

void parse_line(string& line, unordered_map<string, vector<pair<string, int>>>& map, unordered_map<string, int>& bag_count) {
    int i = 0;
    string bag_color = parse_bag_color(line, i);
    bag_count[bag_color] = -1;
    i++;
    parse_word(line, i);
    i++;
    parse_word(line, i);
    i++;
    parse_neighbors(line, i, map, bag_color);
}

int bfs(unordered_map<string, unordered_set<string>>& map) {
    int count = 0;
    queue<string> q;
    unordered_set<string> visited;
    visited.insert("shinygold");
    q.push("shinygold");
    while (!q.empty()) {
        string bag_color = q.front();
        q.pop();
        for (auto parent : map[bag_color]) {
            if (visited.find(parent) == visited.end()) {
                count++;
                visited.insert(parent);
                q.push(parent);
            }
        }
    }
    return count;
}

void dfs(unordered_map<string, bool>& visited, unordered_map<string, vector<pair<string, int>>>& map, unordered_map<string, int>& bag_count, string& curr_bag) {
    visited[curr_bag] = true;
    int total_count = 0;
    for (auto p : map[curr_bag]) {
        string child = p.first;
        int count = p.second;
        if (!visited[child]) {
            if (bag_count[child] == -1) {
                dfs(visited, map, bag_count, child);
            }
            total_count += count;
            total_count += count * bag_count[child];
        }
    }
    bag_count[curr_bag] = total_count;
    visited[curr_bag] = false;
}


int main() {
    unordered_map<string, vector<pair<string, int>>> map;
    unordered_map<string, int> bag_count;
    string line;
    while (getline(cin, line)) {
        parse_line(line, map, bag_count);
    }
    //cout << "Count: " << bfs(map) << endl;
    unordered_map<string, bool> visited;
    string shiny_gold = "shinygold";
    dfs(visited, map, bag_count, shiny_gold);
    cout << "Count: " << bag_count[shiny_gold] << endl; 
    return 0;
}
