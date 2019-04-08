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
        auto ct_orig = new unsigned long long int [L[i]];
        auto ct = new unsigned long long int [L[i]];
        unsigned long long int c;
        vector<unsigned long long int> new_codes;
        set<unsigned long long int> alphabetSet;
        vector<unsigned long long int> alphabet;
        unordered_map<unsigned long long int, unsigned long long int> productToFactorMap;

        istringstream is(CT[i]);
        for (int j = 0; is >> c; j++) {
            ct_orig[j] = c;
            ct[j] = c;
        }
        sort(ct, ct + L[i]);

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