#include <iostream>
#include <string>

using namespace std;

int main() {
    int counts[26] = {0};
    string resp;
    int sum = 0, curr = 0;
    while (getline(cin, resp)) {
        if (resp.size() == 0) {
            for (int i = 0; i < 26; i++) {
                if (counts[i] == curr) {
                    sum++;
                }
                counts[i] = 0;
            }
            curr = 0;
        }
        else {
            curr++;
            for (int i = 0; i < resp.size(); i++) {
                counts[resp[i] - 'a']++;
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        if (counts[i] == curr) {
            sum++;
        }
        counts[i] = 0;
    }
    cout << "Sum: " << sum << endl;
    return 0;
}
