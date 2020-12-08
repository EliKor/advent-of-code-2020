#include <iostream>
#include <string>
#include <vector>

using namespace std;

int run_program(vector<pair<string, int>>& instrs, bool& valid) {
    vector<bool> visited(instrs.size(), false);
    int ip = 0;
    int acc = 0;
    while (ip != instrs.size() + 1) {
        if (ip < 0 || ip > instrs.size() + 1) {
            valid = false;
            break;
        }
        if (visited[ip]) {
            valid = false;
            break;
        }
        visited[ip] = true;
        if (instrs[ip].first == "nop") {
            ip++;
        }
        else if (instrs[ip].first == "jmp") {
            ip += instrs[ip].second;
        }
        else {
            acc += instrs[ip].second;
            ip++;
        }
    }
    return acc;
}

int main() {
    vector<pair<string, int>> instrs;
    string instr;
    while (getline(cin, instr)) {
        string opcode = instr.substr(0, 3);
        int arg = stoi(instr.substr(4));
        instrs.push_back({opcode, arg});
    }
    int acc = 0;
    int i = 0;
    bool valid = false;
    while (i < instrs.size() && !valid) {
        if (instrs[i].first != "acc") {
            valid = true;
            string old_op = instrs[i].first;
            instrs[i].first = old_op == "jmp" ? "nop" : "jmp";
            acc = run_program(instrs, valid);
            instrs[i].first = old_op;
        }
        i++;
    }
    if (valid) {
        cout << "acc: " << acc << endl;
    }
    return 0;
}
