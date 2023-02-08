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

void solve() {
  int n, m;
  cin >> n >> m;

  vi arr(n);
  rep(i, 0, n) { cin >> arr[i]; }

  vector<vector<ll>> dp(n, vector<ll>(m + 2, 0));
  if (arr[0] == 0) {
    rep(j, 1, m + 1) { dp[0][j] = 1; }
  } else {
    dp[0][arr[0]] = 1;
  }

  rep(i, 1, n) {
    rep(j, 1, m + 1) {
      dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]) % mod;
      if (arr[i] != 0 && arr[i] != j) {
        dp[i][j] = 0;
      }
    }
  }

  ll sum = 0;
  rep(j, 0, m + 1) { sum = (sum + dp[n - 1][j]) % mod; }
  print(sum);
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
