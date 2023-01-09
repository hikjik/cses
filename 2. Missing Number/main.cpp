#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = a; i < b; i++)
typedef long long ll;

int main(int argc, char const *argv[]) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  ll sum = n * (n + 1) / 2;
  REP(i, 1, n) {
    ll b;
    cin >> b;
    sum -= b;
  }

  cout << sum << "\n";

  return 0;
}
