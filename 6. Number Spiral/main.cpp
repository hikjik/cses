#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = a; i < b; i++)

typedef long long ll;

int main(int argc, char const *argv[]) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  REP(i, 0, n) {
    ll y, x;
    cin >> y >> x;

    ll m = max(y, x);

    cout << (m - 1) * (m - 1) + m + (x - y) * (m % 2 * 2 - 1) << "\n";
  }

  return 0;
}
