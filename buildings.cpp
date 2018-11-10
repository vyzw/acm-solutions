#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/gym/101873/problem/B

typedef long long ll;
typedef long double ld;

const ll MOD = 1e9+7;

////////////////////////////////////////////////////////////////////////
// Extended Euclidean Algorithm (UBC)
// egcd(a,b,x,y) calculates x,y such that ax+by=gcd(a,b)
// To find a^{-1} mod m, use egcd(a,m,x,y), then x = a^{-1}
// Returns gcd(a,b)
//*!
ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    } else {
        ll d = egcd(b, a%b, y, x);
        y -= x * (a/b);
        return d;
    }
}
//*/

////////////////////////////////////////////////////////////////////////
// Int struct for operations on a prime field (TESTED)
// WARNING: slow
//*!
struct Int {
    ll x;
    Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
    operator ll() { return x; }
    Int operator + (const Int& n) const { return Int(x + n.x); }
    Int operator - (const Int& n) const { return Int(x - n.x); }
    Int operator * (const Int& n) const { return Int(x * n.x); }
    Int operator / (const Int& n) const { return Int(x * n.inv()); }
    void operator += (const Int& n) { x = (x + n.x) % MOD; }
    void operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; }
    void operator *= (const Int& n) { x = (x * n.x) % MOD; }
    void operator /= (const Int& n) { x = (x * n.inv()) % MOD; }
    ll inv() const {
        if (x == 0) throw runtime_error("divide by zero");
        ll c, d;
        egcd(x, MOD, c, d);
        return (c < 0) ? c+MOD : c;
    }
};

Int qpow(int base, int power) {
  Int prod = 1;
  for (int i = 1; i <= power; i++) {
    prod *= Int(base);
  }
  return prod;
}

int main() {
  int n, m, c;
  scanf("%d %d %d", &n, &m, &c);

  Int cn2 = qpow(c,n*n), result = 0;
  Int* numWays = new Int[m+1];
  std::fill(numWays, numWays + m + 1, 0);

  // create array and solve
  for (int f = 1; f <= m; f++) {
    if (m%f == 0) {
      numWays[f] = numWays[f] + qpow(cn2,f);
      result = result + numWays[f]/Int(f);
      for (int i = 2; i*f <= m; i++) {
        numWays[i*f] = numWays[i*f] - numWays[f];
      }
    }
  }
  cout << result << '\n';
  return 0;
}