#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int three_sum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i+1; j < nums.size(); j++) {
            int k = nums.size() - 1;
            while (j < k) {
                if (nums[i] + nums[j] + nums[k] == target) {
                    return nums[i] * nums[j] * nums[k];
                }
                else if (nums[i] + nums[j] + nums[k] < target) {
                    j++;
                }
                else {
                    k--;
                }
            }
        }
    }
    return -1;
}

int two_sum(vector<int>& nums, int target) {
    unordered_set<int> s;
    for (int i = 0; i < nums.size(); i++) {
        auto it = s.find(target-nums[i]);
        if (it != s.end()) {
            return (*it) * nums[i];
        }
        s.insert(nums[i]);
    }
    return -1;
}

int main() {
    vector<int> nums;
    int x;
    for (int i = 0; i < 200; i++) {
        cin >> x;
        nums.push_back(x);
    }
    cout << three_sum(nums, 2020) << endl;
    return 0;
}
