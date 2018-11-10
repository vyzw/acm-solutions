#include <stdio.h>

// https://codeforces.com/group/L0zlhp0AHw/contest/226626/problem/J

int main()
{
    int n, m, a, b, sum = 0;
    scanf("%d %d", &n, &m);
    for (a = 1; m > a * n; a = a * 2) {
        sum = sum + 1;
    }
    b = a*n - m;
    while (a >= 1 && b > 0) {
        sum = sum + (b/a);
        b = b - (b/a)*a;
        a = a/2;
    }
    printf("%d\n", sum);
    return 0;
}