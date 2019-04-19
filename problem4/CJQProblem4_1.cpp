// CJQProblem4_1.cpp : Defines the entry point for the application.
//

#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string toString(vector<int> v) {
    stringstream ss;
    for (size_t i = 0; i < v.size(); i++) {
        ss << v[i];
    }
    return ss.str();
}

vector<int> toVector(string s) {
    vector<int> v(s.size());
    for (size_t i = 0; i < s.size(); i++) {
        v[i] = s[i] == '1';
    }
    return v;
}

void splitSegmentsLenV(vector<int> &v) {
    size_t i = 0;

    while (i < v.size()) {
        int prevSegLen = v[i];
        if (prevSegLen > 1) {
            int segLen = prevSegLen / 2 + (prevSegLen % 2);
            v[i] = segLen;
            v[i + segLen] = prevSegLen - segLen;
        }
        i += prevSegLen;
    }
}

void copyLenV(vector<int> v, vector<int> &tgt) {
    for (size_t i = 0; i < v.size(); i++) {
        tgt[i] = v[i];
    }
}

int main()
{
    int T = 1;

    cerr << "Program started\n";
    cin >> T;
    cerr << "Test cases " << T << "\n";

    for (int i = 0; i < T; i++) {
        int N = 0, B = 0, F = 0;
        cin >> N >> B >> F;
        cerr << "N = " << N << " B = " << B << " F = " << F << "\n";
        vector<int> expInp(N);
        vector<int> countV(N);
        vector<int> lenV(N);

        bool bit = false;
        for (int j = 0; j < N; j++) {
            countV[j] = 0;
            lenV[j] = 0;
            if (j % B == 0) {
                lenV[j] = min(B, N - j);
                if (j > 0) {
                    bit = !bit;
                }
            }
            expInp[j] = bit ? 1 : 0;
        }

        cerr << "First output: " << toString(expInp) << "\n";
        vector<int> lenVPrev(lenV);

        cout << toString(expInp) << "\n";
        cout.clear();

        string resp = "00111011100";

        cin >> resp;
        cerr << "First response: " << resp << "\n";

        vector<int> respV = toVector(resp);

        bit = true;
        int prevSectorEnd;
        int totalFails = 0;
        int sectFails = 0, sectLen = 0, sectStart = 0;

        for (int j = 0; j < N; j++) {
            if (lenV[j] != 0) {
                bit = !bit;
                sectStart = j;
                sectLen = lenV[j];
            }
            if (respV.size() <= j - totalFails || respV[j - totalFails] != expInp[j]) {
                sectFails++;
                totalFails++;
            }
            if (sectStart + sectLen == j + 1) {
                countV[j] = sectFails;
                sectFails = 0;
            }
        }

        bit = true;
        while (lenV[0] > 1) {
            copyLenV(lenV, lenVPrev);
            splitSegmentsLenV(lenV);
            cerr << "lenv: " << toString(lenV) << "\n";
            bit = false;
            for (int j = 0; j < N; j++) {
                if (lenV[j] != 0) {
                    bit = !bit;
                }
                expInp[j] = bit ? 1 : 0;
            }

            cout << toString(expInp) << "\n";
            cout.clear();

            cin >> resp;
            respV = toVector(resp);

            totalFails = 0;
            sectFails = 0;
            int prevSectFailsIdx, prevSectLenIdx, prevSectFails, prevSectPos;
            for (int j = 0; j < N; j++) {
                if (lenV[j] != 0) {
                    sectStart = j;
                    sectLen = lenV[j];
                    if (lenVPrev[j] != 0) {
                        prevSectLenIdx = j;
                        prevSectFailsIdx = j + lenVPrev[j] - 1;
                        prevSectFails = 0;
                        prevSectPos = 0;
                    }
                }

                //if (sectLen > countV[prevSectFailsIdx]) {
                //if (lenVPrev[prevSectLenIdx] > countV[prevSectFailsIdx]) {
                if (prevSectFails < countV[prevSectFailsIdx] && lenVPrev[prevSectLenIdx] - prevSectPos > countV[prevSectFailsIdx]) {
                    if (respV.size() <= j - totalFails || respV[j - totalFails] != expInp[j]) {
                        sectFails++;
                        totalFails++;
                        prevSectFails++;
                        //countV[prevSectFailsIdx]--;
                    }
                }
                else if (prevSectFails < countV[prevSectFailsIdx]) {
                    totalFails += sectLen - sectFails;
                    sectFails = sectLen;
                    j = sectStart + sectLen - 1;
                }

                if (sectStart + sectLen == j + 1) {
                    if (countV[prevSectFailsIdx] > 0) {
                        countV[prevSectFailsIdx] -= sectFails;
                    }
                    countV[j] = sectFails;
                    sectFails = 0;
                }

                prevSectPos++;
                cerr << "countv: " << toString(countV) << "\n";
            }
        }

        stringstream ss;
        for (size_t j = 0; j < countV.size(); j++) {
            if (countV[j]) {
                ss << j << " ";
            }
        }
        cout << ss.str();
    }

    return 0;
}
