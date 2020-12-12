#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void read_vals(vector<int>& vals) {
    int x;
    while (cin >> x) {
        vals.push_back(x);
    }
}

void part1(vector<int>& vals) {
    const int PREAMBLE = 25;
    unordered_map<int, int> map;
    for (int i = 0; i < PREAMBLE; i++) {
        map[vals[i]]++;
    }
    for (int offset = 0; offset < vals.size()-(PREAMBLE+1); offset++) {
        bool found = false;
        for (int i = offset; i < offset+PREAMBLE+1; i++) {
            int target = vals[offset+PREAMBLE+1] - vals[i];
            if (map[target] > 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "First invalid value: " << vals[offset+PREAMBLE+1] << endl;
            return;
        }
        map[vals[offset]]--;
        map[vals[offset+PREAMBLE+1]]++;
    }
}

void part2(vector<int>& vals) {
    const int TARGET = 177777905;
    int start = 0;
    int sum = 0;
    for (int end = 0; end < vals.size(); end++) {
        sum += vals[end];
        while (sum > TARGET) {
            sum -= vals[start];
            start++;
        }
        if (sum == TARGET && end - start > 0) {
            auto minmax = minmax_element(vals.begin() + start, vals.begin() + end + 1);
            cout << "Vulnerability: " << *minmax.first + *minmax.second << endl;
            return;
        }
    }
}


int main() {
    vector<int> vals;
    read_vals(vals);
    part1(vals);
    part2(vals);
    return 0;
}
