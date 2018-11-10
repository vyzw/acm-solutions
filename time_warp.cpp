#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

// https://codeforces.com/gym/100641/attachments

int s1(int h, int angle) {
  return int(((float(h) * 30 + angle) * 120 / 11) + 0.5);
}
int s2(int h, int angle) {
  return int(((float(h) * 30 + angle - 360) * 120 / 11) + 0.5);
}
bool isValid(int S, int dir, int h, int base) {
  if (dir == 1 && S == 0 && h == base) return false;
  return (S >= 0 && S < 3600);
}

int main() {
  const string til = "til";
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int angle, base, h, m, s, dir;
    string direction;
    cin >> angle >> direction >> base;
    if (direction == til) {
      dir = 11;
      h = (base + 11) % 12;
    } else {
      dir = 1;
      h = base;
    }
    for (; true; h = (h+dir)%12) {
      int S1 = s1(h, angle);
      int S2 = s2(h, angle);
      bool b1 = isValid(S1, dir, h, base);
      bool b2 = isValid(S2, dir, h, base);
      if (b1 || b2) {
        int res;
        if (b1 && !b2) res = S1;
        else if (!b1 && b2) res = S2;
        else {
          if (dir == 1) {
            res = (S1 < S2) ? S1 : S2;
          } else {
            res = (S1 > S2) ? S1 : S2;
          }
        }
        if (h == 0) h = 12;
        m = res/60;
        s = res%60;
        break;
      }
    }
    cout << "Case " << i+1 << ": " << h << ":" << ((m < 10) ? "0" : "") << m << ":" << ((s < 10) ? "0" : "") << s << "\n";
  }
  return 0;
}