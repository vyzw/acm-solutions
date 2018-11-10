#include <stdio.h>

// https://codeforces.com/gym/101556/attachments

int main() {
  int n, k, i;
  scanf("%d %d", &n, &k);

  // store probability that largest loop <= k
  double* dp = new double[n + 1];
  for (i = 0; i <= k; i++) {
    dp[i] = 1 + i;
  }
  for (i = k + 1; i <= n; i++) {
    dp[i] = dp[i - 1] + (dp[i - 1] - dp[i - k - 1]) / i;
  }
  printf("%.6lf\n", dp[n] - dp[n - 1]);
}