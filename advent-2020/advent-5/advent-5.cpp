#include <iostream>
#include <string>
#include <vector>

using namespace std;

void find_seat(string& s, bool seats[][8], bool* ids) {
    int row = 0, col = 0;
    int r_lo = 0, r_hi = 128;
    int c_lo = 0, c_hi = 8;
    for (int i = 0; i < 7; i++) {
        int mid = r_lo + (r_hi - r_lo)/2;
        if (s[i] == 'F') {
            r_hi = mid;
        }
        else {
            r_lo = mid;
        }
    }
    row = r_lo;
    for (int i = 7; i < 10; i++) {
        int mid = c_lo + (c_hi - c_lo)/2;
        if (s[i] == 'L') {
            c_hi = mid;
        }
        else {
            c_lo = mid;
        }
    }
    col = c_lo;
    seats[row][col] = true;
    ids[(row*8) + col] = true;
}

int main() {
    int N = 872;
    string s;
    int max_id = 0;
    bool seats[128][8];
    bool ids[936];
    //vector<vector<bool>> seats(128, vector<bool>(8, false));
    //vector<bool> ids(936);
    for (int i = 0; i < N; i++) {
        cin >> s;
        find_seat(s, seats, ids);
    }
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 8; j++) {
            int id = (i*8) + j;
            if (id-1 < 0 || id+1 > 935) {
                continue;
            }
            if (!seats[i][j] && (ids[id-1] && ids[id+1])) {
                cout << "Seat id: " << id << endl;
                break;
            }
        }
    }
    return 0;
}
