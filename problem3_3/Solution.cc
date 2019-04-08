#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <set>
#include <functional>
#include <unordered_map>
#include <iterator>

using namespace std;

bool isLeftGreater(string c1, string c2) {
    int c1Len = c1.size(),
        c2Len = c2.size();

    if (c1Len != c2Len) {
        return c1Len > c2Len;
    }
    else {
        for (int i = 0; i < c1Len; i++) {
            if (c1[i] == c2[i]) {
                continue;
            }
            return c1[i] > c2[i];
        }
    }

    return  false;
}

string subInt(string c1, string c2) {
    string result;
    int c1Len = c1.size(),
        c2Len = c2.size();
    bool prevOver = false;

    for (int i = c1Len - 1, j = c2Len - 1; i >= 0; i--, j--) {
        int diff;
        if (j >= 0) {
            diff = c1[i] - c2[j] - (prevOver ? 1 : 0);
        }
        else {
            diff = c1[i] - '0' - (prevOver ? 1 : 0);
        }
        char c;
        if (diff >= 0) {
            c = '0' + diff;
            prevOver = false;
        }
        else {
            c = '9' + diff + 1;
            prevOver = true;
        }

        result.insert(0, 1, c);
    }

    while (result[0] == '0' && result.size() > 1) {
        result.erase(0, 1);
    }

    return result;
}

string divInt(string c1, string c2) {
    string result;
    int c1Len = c1.size(),
        c2Len = c2.size();

    // cout << "div " << c1 << " " << c2 << "\n";

    string rem = c1.substr(0, c2Len);
    int prevI;
    int i = c2Len;
    do {
        prevI = i + 1;
        while (isLeftGreater(c2, rem)) {
            rem += c1[i++];
        }
        char div = '0';
        do {
            div++;
            rem = subInt(rem, c2);
        } while (isLeftGreater(rem, c2) || rem == c2);
        while (prevI < i) {
            result += '0';
            prevI++;
        }
        result += div;
        // cout << result << "\n";
    } while (i < c1Len);

    return result;
}

int main() {
    int T;
    string line;
    getline(cin, line);
    T = atoi(line.c_str());

    vector<unsigned long long int> N;
    vector<int> L;
    vector<string> CT;

    cout << divInt("5736877719", "573") << "\n";

    // for (int i = 0; i < T; i++) {
    //     int n;
    //     int l;
    //     getline(cin, line);

    //     if (cin.fail()) {
    //         cin.clear();
    //         cin.ignore(numeric_limits<streamsize>::max());
    //     }

    //     l = atoi(line.substr(line.find(" ")).c_str());

    //     getline(cin, line);

    //     if (cin.fail()) {
    //         cin.clear();
    //         cin.ignore(numeric_limits<streamsize>::max());
    //     }

    //     L.push_back(l);
    //     CT.push_back(line);
    // }

    // for (int i = 0; i < T; i++) {
    //     string c;
    //     set<string> alphabetSet;
    //     vector<string> alphabet;

    //     istringstream is(CT[i]);
    //     vector<string> ct(istream_iterator<string>{is}, istream_iterator<string>());

    //     int diffidx = 0;

    //     while (ct[diffidx] == ct[diffidx + 1]) {
    //         diffidx++;
    //     }

    //     string c1 = ct[diffidx], c2 = ct[diffidx + 1], cd;

    //     while (c1 != c2) {
    //         if (isLeftGreater(c1, c2)) {
    //             c1 = subInt(c1, c2);
    //         }
    //         else {
    //             c2 = subInt(c2, c1);
    //         }
    //     }
    //     cd = c1;

    //     auto letter = cd = divInt(ct[diffidx], cd);

    //     alphabetSet.insert(cd);
    //     alphabet.push_back(cd);

    //     for (int j = diffidx; j < L[i]; j++) {
    //         cd = divInt(ct[j], cd);
    //         if (alphabetSet.find(cd) == alphabetSet.end()) {
    //             alphabetSet.insert(cd);
    //             alphabet.push_back(cd);
    //         }
    //     }

    //     sort(alphabet.begin(), alphabet.end(), [](string &c1, string &c2) { return isLeftGreater(c2, c1); });

    //     // for (auto a : alphabet) {
    //     //     cout << " " << a;
    //     // }
    //     // cout << "\n";

    //     string codeLine = "";

    //     int idx = find(alphabet.begin(), alphabet.end(), letter) - alphabet.begin();
    //     codeLine += 65 + idx;

    //     for (int j = 0; j < L[i]; j++) {
    //         letter = divInt(ct[j], letter);
    //         idx = find(alphabet.begin(), alphabet.end(), letter) - alphabet.begin();
    //         codeLine += 65 + idx;
    //     }

    //     cout << "Case #" << i+1 << ": " << codeLine << "\n";
    // }

    return 0;
}

