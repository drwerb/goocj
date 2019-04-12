#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <set>
#include <functional>
#include <unordered_map>
#include <iterator>

using namespace std;

class BigInt {
private:
public:
    static int resultBuf[200];
    int* num;
    int len;

    BigInt() {
        len = 0;
        num = new int[200];
    }

    BigInt(string s) {
        len = s.size();
        num = new int[200];
        for (int i = 0; i < len; i++) {
            num[i] = s[len - i - 1] - '0';
        }
    }

    BigInt(int l, int* n) {
        len = l;
        num = n;
    }

    ~BigInt() {
        delete[] num;
    }

    BigInt* clone() {
        int * newNum = new int[200];
        for (int i = 0; i < len; i++) {
            newNum[i] = num[i];
        }
        return new BigInt(len, newNum);
    }

    void set(int l, int* n, int start) {
        len = l;
        for (int i = 0; i < len; i++) {
            num[i] = n[i + start];
        }
    }

    void setHigh(int l, int* n, int start) {
        len = l + start;
        for (int i = 0; i < start; i++) {
            num[i] = 0;
        }
        for (int i = 0; i < l; i++) {
            num[i] = n[i + start];
        }
    }

    bool isZero() {
        return num[0] == 0 && len == 1 || len == 0;
    }

    void prepend(int d) {
        len++;
        int tmp;
        for (int i = 0; i < len; i++) {
            tmp = num[i];
            num[i] = d;
            d = tmp;
        }
    }

    bool isGreaterThan(BigInt *c2) {
        if (len != c2->len) {
            return len > c2->len;
        }
        else {
            for (int i = len - 1; i >= 0; i--) {
                if (num[i] == c2->num[i]) {
                    continue;
                }
                return num[i] > c2->num[i];
            }
        }

        return  false;
    }

    void sub(BigInt* c2, BigInt *tgt) {
        int resLen = len;
        bool prevOver = false;

        for (int i = 0, j = 0; i < len; i++, j++) {
            int diff;
            if (j < c2->len) {
                diff = num[i] - c2->num[j] - (prevOver ? 1 : 0);
            }
            else {
                diff = num[i] - (prevOver ? 1 : 0);
            }
            int c;
            if (diff >= 0) {
                c = diff;
                prevOver = false;
            }
            else {
                c = 10 + diff;
                prevOver = true;
            }

            BigInt::resultBuf[i] = c;
        }

        while (BigInt::resultBuf[resLen - 1] == 0 && resLen > 1) {
            resLen--;
        }

        tgt->set(resLen, BigInt::resultBuf, 0);
    }

    void div(BigInt* c2, BigInt *tgt) {
        // cout << "div " << c1 << " " << c2 << "\n";

        BigInt* rem = new BigInt(c2->len + 1, new int[200]);
        rem->set(c2->len, num, len - c2->len);
        int prevI;
        int i = c2->len;
        int resI = 0;
        do {
            prevI = i;
            while (c2->isGreaterThan(rem) && i < len) {
                if (rem->isZero()) {
                    rem->len = 0;
                }
                if (i > prevI) {
                    BigInt::resultBuf[resI++] = 0;
                }
                rem->prepend(num[len - ++i]);
            }
            if (i >= len && rem->isZero()) {
                BigInt::resultBuf[resI++] = 0;
                break;
            }
            int div = 0;
            do {
                div++;
                rem->sub(c2, rem);
            } while (!c2->isGreaterThan(rem));
            BigInt::resultBuf[resI++] = div;
            // cout << result << "\n";
        } while (i < len);

        delete rem;

        int temp;
        int resLen = resI;
        for (i = 0; i < resLen / 2; i++)
        {
            temp = BigInt::resultBuf[i];
            BigInt::resultBuf[i] = BigInt::resultBuf[resLen - i - 1];
            BigInt::resultBuf[resLen - i - 1] = temp;
        }

        tgt->set(resLen, BigInt::resultBuf, 0);
    }

    void sum(BigInt* c2, BigInt *tgt) {
        int resLen = max(len, c2->len);
        bool prevOver = false;
        int diff;

        for (int i = 0; i < resLen; i++) {
            if (i < c2->len && i < len) {
                diff = num[i] + c2->num[i] + (prevOver ? 1 : 0);
            }
            else if ( i < len ) {
                diff = num[i] + (prevOver ? 1 : 0);
            }
            else {
                diff = c2->num[i] + (prevOver ? 1 : 0);
            }
            int c;
            if (diff >= 10) {
                c = diff - 10;
                prevOver = true;
            }
            else {
                c = diff;
                prevOver = false;
            }

            BigInt::resultBuf[i] = c;
        }

        if (prevOver) {
            BigInt::resultBuf[resLen++] = 1;
        }

        tgt->set(resLen, BigInt::resultBuf, 0);
    }

    void mul(BigInt* c2, BigInt *tgt) {
        BigInt *buf1 = new BigInt();
        BigInt *buf2 = new BigInt();
        for (int i = 0; i < len; i++) {
            buf2->setHigh(c2->len, c2->num, i);
            if (num[i] == 0 && buf1->len == i) {
                buf1->num[i] = 0;
                buf1->len++;
                continue;
            }
            for (int j = 0; j < num[i]; j++) {
                buf1->sum(buf2, buf1);
            }
        }
        tgt->set(buf1->len, buf1->num, 0);
    }

    string toString() {
        string result = "";

        for (int i = len - 1; i >= 0; i--) {
            result += '0' + num[i];
        }

        return result;
    }

    bool equals(BigInt* c) {
        if (len != c->len) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            if (num[i] != c->num[i]) {
                return false;
            }
        }
        return true;
    }
};

int BigInt::resultBuf[200];

bool isLeftGreater(string &c1, string &c2) {
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

BigInt** parse(const char* line, int lineLength, int numCount) {
    BigInt** ct = new BigInt*[numCount];
    int * buf = new int[200];
    int numLen, i, j;
    int linePos = 0;
    for (i = 0; i < numCount; i++) {
        numLen = 0;
        while (line[linePos] >= '0' && line[linePos] <= '9' && linePos < lineLength) {
            buf[numLen++] = line[linePos] - '0';
            linePos++;
        }
        linePos++;
        int * intArr = new int[200];
        for (j = 0; j < numLen; j++) {
            intArr[numLen - j - 1] = buf[j];
        }
        ct[i] = new BigInt(numLen, intArr);
    }
    delete buf;
    return ct;
}

int findAlpha(BigInt **arr, int len, BigInt *a) {
    for (int i = 0; i < len; i++) {
        if (arr[i]->equals(a)) {
            return i;
        }
    }

    return -1;
}

bool readFromStd = false;

int main() {
    int T;
    string line;

    char* line_c;
    BigInt** ct;
    BigInt** alphabet = new BigInt*[26];

    for (int i = 0; i < 26; i++) {
        alphabet[i] = new BigInt();
    }

    int alphaNextIdx;

    vector<unsigned long long int> N;
    vector<int> L;
    vector<string> CT;

    auto b = new BigInt("400");
    b->mul(new BigInt("400"), b);
    cout << b->toString() << "\n";

    //if (readFromStd) {
    //    getline(cin, line);
    //    T = atoi(line.c_str());
    //    for (int i = 0; i < T; i++) {
    //        int n;
    //        int l;
    //        getline(cin, line);

    //        if (cin.fail()) {
    //            cin.clear();
    //            cin.ignore(numeric_limits<streamsize>::max());
    //        }

    //        l = atoi(line.substr(line.find(" ")).c_str());

    //        getline(cin, line);

    //        if (cin.fail()) {
    //            cin.clear();
    //            cin.ignore(numeric_limits<streamsize>::max());
    //        }

    //        L.push_back(l);
    //        CT.push_back(line);
    //    }
    //}
    //else {
    //    ifstream inp("C:\\Users\\vverblyudov\\source\\repos\\CJProblem3_4\\data.inp");
    //    getline(inp, line);
    //    T = atoi(line.c_str());
    //    for (int i = 0; i < T; i++) {
    //        int n;
    //        int l;
    //        getline(inp, line);

    //        l = atoi(line.substr(line.find(" ")).c_str());

    //        getline(inp, line);

    //        L.push_back(l);
    //        CT.push_back(line);
    //    }
    //}

    //for (int i = 0; i < T; i++) {
    //    alphaNextIdx = 0;
    //    ct = parse(CT[i].c_str(), CT[i].size(), L[i]);

    //    int diffidx = 0;

    //    while (!ct[diffidx]->isGreaterThan(ct[diffidx + 1]) && !ct[diffidx + 1]->isGreaterThan(ct[diffidx])) {
    //        diffidx++;
    //    }

    //    BigInt *c1 = ct[diffidx]->clone(), *c2 = ct[diffidx + 1]->clone(), *cd, *tmp;

    //    while (!c1->equals(c2)) {
    //        if (c1->isGreaterThan(c2)) {
    //            c1->sub(c2, c1);
    //        }
    //        else {
    //            c2->sub(c1, c2);
    //        }
    //    }

    //    cd = c1->clone();

    //    delete c1;
    //    delete c2;

    //    ct[diffidx]->div(cd, cd);

    //    BigInt *firstLetter = cd->clone();

    //    alphabet[alphaNextIdx++]->set(firstLetter->len, firstLetter->num, 0);

    //    for (int j = diffidx; j < L[i]; j++) {
    //        ct[j]->div(cd, cd);
    //        if (findAlpha(alphabet, alphaNextIdx, cd) == -1) {
    //            alphabet[alphaNextIdx++]->set(cd->len, cd->num, 0);
    //        }
    //    }

    //    delete cd;

    //    sort(alphabet, alphabet + 25, [](BigInt *c1, BigInt *c2) { return c2->isGreaterThan(c1); });

    //    // for (auto a : alphabet) {
    //    //     cout << " " << a;
    //    // }
    //    // cout << "\n";

    //    string codeLine = "";

    //    int idx = findAlpha(alphabet, alphaNextIdx, firstLetter);
    //    codeLine += 65 + idx;

    //    BigInt *letter = firstLetter->clone();

    //    for (int j = 0; j < L[i]; j++) {
    //        ct[j]->div(letter, letter);
    //        idx = findAlpha(alphabet, alphaNextIdx, letter);
    //        codeLine += 65 + idx;
    //    }

    //    delete letter;

    //    for (int j = 0; j < L[i]; j++) {
    //        delete ct[j];
    //    }

    //    cout << "Case #" << i + 1 << ": " << codeLine << "\n";
    //}

    if (!readFromStd) {
        cin.get();
    }

    return 0;
}

