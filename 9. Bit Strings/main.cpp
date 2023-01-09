#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(int argc, char const *argv[]) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  ll res = 1;
  ll x = 2;
  int m = 1e9 + 7;
  while (n > 0) {
    if (n & 1) {
      res = (res * x) % m;
    }

    n >>= 1;
    x = (x * x) % m;
  }
  cout << res << "\n";

  return 0;
}
