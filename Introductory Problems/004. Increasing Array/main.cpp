#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define REP(i, a, b) for (int i = a; i < b; i++)

int main(int argc, char const *argv[]) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  int prev = 0;
  ll count = 0;
  REP(i, 0, n) {
    int b;
    cin >> b;
    if (i == 0) {
      prev = b;
    } else {
      if (b < prev) {
        count += prev - b;
      } else {
        prev = b;
      }
    }
  }

  cout << count << "\n";

  return 0;
}
