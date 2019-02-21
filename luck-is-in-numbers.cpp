#include <iostream>
using namespace std;

// http://codeforces.com/contest/120/problem/I

const int digits[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
int** lucky;
string coppy;

int luckiness (int d1, int d2) {
    // luckiness of two digits on top of each other
    int x = digits[d1], y = digits[d2];
    int diff = 64;
    int luck = 0;
    while (diff >= 1) {
        if (x>= diff && y>=diff) luck+=1;
        x %= diff;
        y %= diff;
        diff /= 2;
    }
    return luck;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    lucky = new int*[10];
    for (int i = 0; i < 10; i++) {
        lucky[i] = new int[10];
        for (int j = 0; j < 10; j++) {
            int temp = luckiness(i,j);
            lucky[i][j] = temp;
        }
    }

    string num;
    cin >> num;
    
    for (int i = 0; i < num.length(); i++) {
        coppy += num[i];
    }

    int n = num.length()/2;
    int* best = new int[2*n+1]; // best diff in sum if i change the last (index) digits (not necessarily to bigger)
    int i, j;
    for (i = 0; i <= 2*n; i++) best[i] = 0;
    for (i = 1; i <= 2*n; i++) {
        // can I increase luckiness by only changing the last i digits, and changing the ith-last digit to be bigger?
        int lhs, rhs;
        if (i <= n) {
            lhs = num[n-i]-'0', rhs = num[2*n-i]-'0';
        } else {
            lhs = num[2*n-i]-'0', rhs = num[3*n-i]-'0';
        }

        for (j = 0; j < 10; j++) {
            if (i <= n) {
                if (lucky[lhs][j] - lucky[lhs][rhs] + best[i-1] > best[i]) {
                    best[i] = lucky[lhs][j] - lucky[lhs][rhs] + best[i-1];
                }
                if (j > rhs && lucky[lhs][j] - lucky[lhs][rhs] + best[i-1] > 0) {
                    break;
                }
            } else {
                if (best[i-1] + lucky[j][j] - lucky[lhs][rhs] - best[i-n] + best[i-n-1] > best[i]) {
                    best[i] = best[i-1] + lucky[j][j] - lucky[lhs][rhs] - best[i-n] + best[i-n-1];
                    // best[i] should store (i-n)*7 - matches + best[n] - best[i-n]
                }
                if (j > lhs && best[i-1] + lucky[j][j] - lucky[lhs][rhs] - best[i-n] + best[i-n-1] > 0) {
                    break;
                }
            }
        }
        if (j != 10) {
            break;
        }
    }

    if (i <= 2*n) {
        // change the ith last digit to j
        // then greedily find least number
        if (i <= n) {
            int lhs = num[n-i]-'0', rhs = num[2*n-i]-'0';
            int diff = lucky[lhs][j] - lucky[lhs][rhs];
            coppy[2*n-i] = j+'0';
            i--;
            while (i > 0) {
                lhs = num[n-i]-'0', rhs = num[2*n-i]-'0';
                for (int j = 0; j < 10; j++) {
                    if (diff + lucky[lhs][j] - lucky[lhs][rhs] + best[i-1] > 0) {
                        diff += lucky[lhs][j] - lucky[lhs][rhs];
                        coppy[2*n-i] = j+'0';
                        break;
                    }
                }
                i--;
            }
        } else {
            int spending = 0;
            for (int k = 0; k < 2*n-i; k++) {
                spending += lucky[num[k]-'0'][num[k]-'0'] - lucky[num[k]-'0'][num[n+k]-'0'];
            }
            spending += lucky[j][j] - lucky[num[2*n-i]-'0'][num[3*n-i]-'0'];
            for (int k = 2*n-i+1; k < n; k++) {
                spending += lucky[8][8] - lucky[num[k]-'0'][num[n+k]-'0'];
            }
            coppy[2*n-i] = j+'0';
            i--;
            while (i > n) {
                for (int j = 0; j < 10; j++) {
                    if (spending + lucky[j][j] - lucky[8][8] > 0) {
                        coppy[2*n-i] = j+'0';
                        coppy[3*n-i] = j+'0';
                        spending += lucky[j][j] - lucky[8][8];
                        break;
                    }
                }
                i--;
            }
            
            while (i >= 1) {
              
                int lhs = coppy[n-i]-'0';
                for (int j = 0; j < 10; j++) {
                  
                    if (spending + lucky[lhs][j] - lucky[lhs][lhs] > 0) {
                        spending += lucky[lhs][j] - lucky[lhs][lhs];
                        coppy[2*n-i] = j+'0';
                        break;
                    }
                }
                i--;
            }
        }
        cout << coppy << '\n';
    } else {
        
        cout << "-1\n";
    }

    return 0;
}