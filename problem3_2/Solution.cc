#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <set>
#include <functional>
#include <unordered_map>

using namespace std;

int main() {
    int T;
    string line;
    getline(cin, line);
    T = atoi(line.c_str());

    vector<unsigned long long int> N;
    vector<int> L;
    vector<string> CT;

    for (int i = 0; i < T; i++) {
        int n;
        int l;
        getline(cin, line);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
        }

        l = atoi(line.substr(line.find(" ")).c_str());

        getline(cin, line);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
        }

        L.push_back(l);
        CT.push_back(line);
    }

    for (int i = 0; i < T; i++) {
        vector<unsigned long long int> ct_orig;
        vector<unsigned long long int> ct;
        unsigned long long int c;
        vector<unsigned long long int> new_codes;
        set<unsigned long long int> alphabetSet;
        vector<unsigned long long int> alphabet;
        unordered_map<unsigned long long int, unsigned long long int> productToFactorMap;

        L[i] = 0;

        string ct_str = CT[i];
        int prevPos = 0, pos = 0, ct_len = 0;

        while (true) {
            pos = ct_str.find(' ', prevPos + 1);
            if (pos == string::npos) {
                pos = ct_str.length();
            }

            if (pos == prevPos + 1) {
                prevPos = pos;
                if (pos == ct_str.length()) {
                    break;
                }
                continue;
            }

            c = atoi(ct_str.substr(prevPos, pos - prevPos).c_str());
            ct.push_back(c);
            ct_orig.push_back(c);
            L[i]++;

            // cout << c << "\n";

            if (pos == ct_str.length()) {
                break;
            }

            prevPos = pos;
        }

        // cout << ct_len << "\n";
        sort(ct.begin(), ct.end());

        unsigned long long int f1;

        f1  = static_cast<unsigned long long int>(sqrt(ct[0]));

        while (f1 > 1 && (ct[0] % f1 != 0)) {
            f1--;
        }

        alphabetSet.insert(f1);
        alphabet.push_back(f1);
        new_codes.push_back(f1);
        productToFactorMap[ct[0]] = f1;

        while (!new_codes.empty()) {
            f1 = new_codes[0];
            new_codes.erase(new_codes.begin());
            for (int j = 0; j < L[i]; j++) {
                if (ct_orig[j] % f1 == 0) {
                    auto f2 = ct_orig[j] / f1;
                    if (alphabetSet.find(f2) == alphabetSet.end()) {
                        alphabetSet.insert(f2);
                        alphabet.push_back(f2);
                        new_codes.push_back(f2);
                        productToFactorMap[ct_orig[j]] = f2;
                    }
                }
            }
        }

        sort(alphabet.begin(), alphabet.end());

        string codeLine = "";
        auto letter = productToFactorMap[ct_orig[0]];

        if (ct_orig[1] % letter == 0) {
            letter = ct_orig[0] / letter;
        }

        int idx = find(alphabet.begin(), alphabet.end(), letter) - alphabet.begin();
        codeLine += 65 + idx;

        for (int j = 0; j < L[i]; j++) {
            letter = ct_orig[j] / letter;
            idx = find(alphabet.begin(), alphabet.end(), letter) - alphabet.begin();
            codeLine += 65 + idx;
        }

        cout << "Case #" << i+1 << ": " << codeLine << "\n";
    }

    return 0;
}