#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N;
vector<string> programs(255);
vector<int> idxs(255);
vector<bool> passed(255);
string answ;
char c;
bool P = false, S = false, R = false;
int cnt;

string solve() {
    cin >> N;

    // cerr << N << "\n";

    for (int j=0; j < N; j++) {
        cin >> programs[j];
        // cerr << programs[j] << "\n";
        idxs[j] = 0;
        passed[j] = false;
    }

    answ = "";
    cnt = 0;

    while (cnt < N) {

        P = false;
        S = false;
        R = false;
        for (int j=0; j < N; j++) {
            if (!P)
                P = programs[j][idxs[j]] == 'P';
            if (!S)
                S = programs[j][idxs[j]] == 'S';
            if (!R)
                R = programs[j][idxs[j]] == 'R';
        }

        if (!P && !R && S) {
            c = 'R';
        }
        else if (!P && R && !S) {
            c = 'P';
        }
        else if (P && !R && !S) {
            c = 'S';
        }
        else if (P && R && !S) {
            c = 'P';
        }
        else if (P && !R && S) {
            c = 'S';
        }
        else if (!P && R && S) {
            c = 'R';
        }
        else {
            answ = "IMPOSSIBLE";
            break;
        }

        answ += c;

        if (answ.size() > 500) {
            answ = "IMPOSSIBLE";
            break;
        }

        for (int j=0; j < N; j++) {

            if (passed[j]) {
                idxs[j] = (idxs[j] + 1) % programs[j].size();
                continue;
            }

            if (programs[j][idxs[j]] == 'P' && c == 'S') {
                passed[j] = true;
                cnt++;
            }
            if (programs[j][idxs[j]] == 'R' && c == 'P') {
                passed[j] = true;
                cnt++;
            }
            if (programs[j][idxs[j]] == 'S' && c == 'R') {
                passed[j] = true;
                cnt++;
            }
            idxs[j] = (idxs[j] + 1) % programs[j].size();
        }

    }

    return answ;
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {

        cout << "Case #" << i + 1 << ": " << solve() << "\n";
    }

    return 0;
}