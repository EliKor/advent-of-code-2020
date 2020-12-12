#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void part1(vector<int> adaptors) {
    adaptors.push_back(0);
    sort(adaptors.begin(), adaptors.end());
    vector<int> diffs(4, 0);
    for (int i = 1; i < adaptors.size(); i++) {
        diffs[adaptors[i] - adaptors[i-1]]++; 
    }
    cout << "Differences Multiplied: " << diffs[1] * (diffs[3] + 1) << endl;
}

void part2(vector<int> adaptors) {
    adaptors.push_back(0);
    sort(adaptors.begin(), adaptors.end());
    unordered_map<int, long long> map;
    map[adaptors[adaptors.size()-1]] = 1;
    for (int i = adaptors.size()-2; i >= 0; i--) {
        for (int j = 1; j <= 3; j++) {
            map[adaptors[i]] += map[adaptors[i]+j];
        }
    }
    cout << "Ways: " << map[adaptors[0]] << endl;
}

int main() {
    vector<int> adaptors;
    int x;
    while (cin >> x) {
        adaptors.push_back(x);
    }
    part1(adaptors);
    part2(adaptors);
    return 0;
}
