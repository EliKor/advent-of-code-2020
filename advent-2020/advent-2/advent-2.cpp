#include <iostream>
#include <string>

using namespace std;

bool is_valid(int lo, int hi, char c, string& password) {
    int counts[26] = {0};
    for (int i = 0; i < password.size(); i++) {
        counts[password[i] - 'a']++;
    }
    return counts[c - 'a'] <= hi && counts[c - 'a'] >= lo;
}

bool is_valid2(int lo, int hi, char c, string& password) {
    return (password[lo-1] == c) ^ (password[hi-1] == c);
}


int main() {
    int N = 1000;
    int lo;
    int hi;
    char dash;
    char c;
    char colon;
    string password;
    int valid = 0;
    for (int i = 0; i < N; i++) {
        cin >> lo >> dash >> hi >> c >> colon >> password;
        valid += is_valid2(lo, hi, c, password);
    }
    cout << "Valid: " << valid << endl;
    return 0;
}
