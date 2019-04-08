#include <iostream>
#include <vector>

using namespace std;

int main() {
    int T;

    cin >> T;

    vector<string> N;
    vector<string> P;

    for (int i = 0; i < T; i++) {
        string path, len;
        cin >> len;
        cin >> path;
        N.push_back(len);
        P.push_back(path);
    }

    for (int i = 0; i < T; i++) {
        string myPath = "";
        for (auto c : P[i]) {
            myPath += c == 'S' ? 'E' : 'S';
        }
        cout << "Case #" << i+1 << ": " << myPath << "\n";
    }
}