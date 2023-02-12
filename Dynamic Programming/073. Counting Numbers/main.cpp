#include <bits/stdc++.h>
using namespace std;

// #define int long long int
#define endl "\n"
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define repr(i, a, b) for (int i = a; i >= b; i--)
#define fastio()                                                               \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define mod 1000000007 // 1e9+7
#define inf 1e18       // 1e18
#define PI 3.1415926535897932384626
#define setbits(x) __builtin_popcountll(x)
#define zrobits(x) __builtin_ctzll(x)
#define ps(x, y) fixed << setprecision(y) << x
#define mk(arr, n, type) type *arr = new type[n];
#define w(x)                                                                   \
  int x;                                                                       \
  cin >> x;                                                                    \
  while (x--)
#define print(x) cout << x << endl;
#define print2(x, y) cout << x << " " << y << endl;
#define print3(x, y, z) cout << x << " " << y << " " << z << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
// online judge
void online_judge() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
}

ll DP[20][10][2][2];

ll compute(const string &number, size_t n, int previous_digit,
           int leading_zeros, int tight) {
  if (n == 0) {
    return 1;
  }

  ll &total = DP[n][previous_digit][leading_zeros][tight];

  if (previous_digit != -1 && total != -1) {
    return total;
  }

  int lower = 0;
  int upper = tight ? number[number.size() - n] - '0' : 9;

  total = 0;
  rep(digit, lower, upper + 1) {
    if (digit == previous_digit && !leading_zeros) {
      continue;
    }
    total += compute(number, n - 1, digit, leading_zeros && !digit,
                     tight && digit == upper);
  }
  return total;
}

ll compute(ll number) {
  memset(DP, -1, sizeof(DP));
  const string number_str = to_string(number);
  return compute(number_str, number_str.size(), -1, 1, 1);
}

void solve() {
  ll a, b;
  cin >> a >> b;
  print(compute(b) - compute(a - 1));
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
