#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(int argc, char const *argv[]) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  int r = n % 4;
  if (r == 1 || r == 2) {
    cout << "NO\n";
    return 0;
  }

  cout << "YES\n";
  cout << (n + 1) / 2 << "\n";
  if (r == 0) {
    for (int i = 1; i <= n; i += 4) {
      cout << i << " ";
    }
    for (int i = 4; i <= n; i += 4) {
      cout << i << " ";
    }
  } else {
    for (int i = 4; i <= n; i += 4) {
      cout << i << " ";
    }
    for (int i = 7; i <= n; i += 4) {
      cout << i << " ";
    }
    cout << 1 << " " << 2 << " ";
  }
  cout << "\n";

  cout << n / 2 << "\n";
  if (r == 0) {
    for (int i = 2; i <= n; i += 4) {
      cout << i << " ";
    }
    for (int i = 3; i <= n; i += 4) {
      cout << i << " ";
    }
  } else {
    for (int i = 5; i <= n; i += 4) {
      cout << i << " ";
    }
    for (int i = 6; i <= n; i += 4) {
      cout << i << " ";
    }
    cout << 3 << " ";
  }
  cout << "\n";

  return 0;
}
