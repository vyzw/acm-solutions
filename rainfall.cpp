#include <stdio.h>
#include <math.h>

// https://codeforces.com/gym/100800/attachments

int main() {
  int t;
  float c, d;
  scanf("%d", &t);
  scanf("%f %f", &c, &d);

  int* r = new int[t + 1];
  r[0] = 0;
  for (int i = 1; i <= t; i++) {
    // prefix sum
    int r_i;
    scanf("%d", &r_i);
    r[i] = r[i - 1] + r_i;
  }

  // assume best intervals are at the minute marks
  float leastWet = -1;
  for (int i = 1; i <= t; i++) {
    float v = d / i * 60;
    float sweat = c * v * v * i;
    int bestStart = 0;
    for (int j = 1; j + i <= t; j++) {
      if (r[j + i] - r[j] < r[bestStart + i] - r[bestStart]) {
        bestStart = j;
      }
    }
    float wet = r[bestStart + i] - r[bestStart] + sweat;
    float s = r[bestStart+1]-r[bestStart], e = r[bestStart+i]-r[bestStart+i-1];
    float heavyRain = s > e ? s : e;
    if (heavyRain != 0){
      //do some calculus
      float t = 60*sqrt(c*d*d/heavyRain);
      if (t >= i -1 && t <= i) {
        if (heavyRain == s) {
          wet = r[bestStart+i]-r[bestStart+1];
        } else {
          wet = r[bestStart + i-1]-r[bestStart];
        }
        wet = wet + (t-i+1)*heavyRain;
        v = d/t*60;
        sweat = c*v*v*t;
        wet = wet+sweat;
      }
    }
    if (wet < leastWet || leastWet < 0) {
      leastWet = wet;
    }
  }

  printf("%f\n", leastWet);
}