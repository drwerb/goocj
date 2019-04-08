#include <iostream>
#include <vector>

using namespace std;

int main() {
    int T;

    cin >> T;

    vector<string> N;

    for (int i = 0; i < T; i++) {
        string num;
        cin >> num;
        N.push_back(num);
    }

    for (int i = 0; i < T; i++) {
        bool hasFour = false;
        string A = "", B = "";
        for (auto c : N[i]) {
            if (c == '4') {
                A += "2";
                B += "2";
                hasFour = true;
            }
            else {
                A += c;
                if (hasFour) {
                    B += "0";
                }
            }
        }

        if (!hasFour) {
            B += "0";
        }

        cout << "Case #" << i+1 << ": " << A << " " << B << "\n";
    }
}