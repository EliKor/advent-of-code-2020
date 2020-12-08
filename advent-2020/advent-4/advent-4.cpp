#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

bool validate_year(string& val, int lo, int hi) {
    if (val.size() != 4) {
        return false;
    }
    long year = 0;
    for (int i = 0; i < 4; i++) {
        year *= 10;
        year += val[i] - '0';
    }
    return lo <= year && year <= hi;
}

bool validate_height(string& val) {
    if (val.size() < 4 || val.size() > 5) {
        return false;
    }
    long height = 0;
    for (int i = 0; i < val.size() - 2; i++) {
        height *= 10;
        height += val[i] - '0';
    }
    if (val.substr(val.size()-2, 2) == "cm") {
        return 150 <= height && height <= 193;
    }
    else if (val.substr(val.size()-2, 2) == "in") {
        return 59 <= height && height <= 76;
    }
    return false;
}

bool validate_hair_color(string& val) {
    if (val.size() != 7 || val[0] != '#') {
        return false;
    }
    for (int i = 1; i < 7; i++) {
        if ((val[i] - '0' > 9 || val[i] - '0' < 0) && (val[i] - 'a' > 5 || val[i] - 'a' < 0)) {
            return false;
        }
    }
    return true;
}

bool validate_eye_color(string& val) {
    return val.size() == 3 &&
           (val == "amb"
           || val == "blu"
           || val == "brn"
           || val == "gry"
           || val == "grn"
           || val == "hzl"
           || val == "oth");
}

bool validate_passport_id(string& val) {
    if (val.size() != 9) {
        return false;
    }
    for (int i = 0; i < 9; i++) {
        if (val[i] - '0' < 0 || val[i] - '0' > 9) {
            return false;
        }
    }
    return true;
}

bool is_valid(string& key, string& val) {
    if (key == "byr") {
        return validate_year(val, 1920, 2002);
    }
    else if (key == "iyr") {
        return validate_year(val, 2010, 2020);
    }
    else if (key == "eyr") {
        return validate_year(val, 2020, 2030);
    }
    else if (key == "hgt") {
        return validate_height(val);
    }
    else if (key == "hcl") {
        return validate_hair_color(val);
    }
    else if (key == "ecl") {
        return validate_eye_color(val);
    }
    else if (key == "pid") {
        return validate_passport_id(val);
    }
    else if (key == "cid") {
        return true;
    }
    return false;
}

void add_fields(unordered_set<string>& field_set, string& fields) {
    string key_val = "";
    for (int i = 0; i < fields.size(); i++) {
        if (fields[i] == ' ' && key_val.size() > 0) {
            string key = key_val.substr(0, 3);
            string val = key_val.substr(4);
            if (is_valid(key, val)) {
                field_set.insert(key);
            }
            key_val = "";
            continue;
        }
        key_val.push_back(fields[i]);
    }
    if (key_val.size() > 0) {
        string key = key_val.substr(0, 3);
        string val = key_val.substr(4);
        if (is_valid(key, val)) {
            field_set.insert(key);
        }
    }
}

int main() {
    string fields;
    unordered_set<string> field_set;
    int valid = 0;
    int passport_count = 1;
    while (getline(cin, fields)) {
        if (fields.size() == 0) {
            valid += (field_set.size() == 8
                  || (field_set.size() == 7 && field_set.find("cid") == field_set.end()));
            field_set.clear();
            continue;
        }
        add_fields(field_set, fields);
    }
    valid += (field_set.size() == 8
                  || (field_set.size() == 7 && field_set.find("cid") == field_set.end()));
    cout << "Valid: " << valid << endl;
    return 0;
}
