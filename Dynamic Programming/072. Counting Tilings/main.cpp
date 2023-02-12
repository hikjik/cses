#include <bits/stdc++.h>
using namespace std;

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

const int MAX_M = 1000;
const int MAX_N = 10;

// DP[i][k] - number of ways to fully cover first i−1 columns and have a
// mask k on the ith column where every set bit in k corresponds to an already
// occupied cell and unset bit to unoccupied cells.
int DP[MAX_M + 1][1 << MAX_N];
int n, m;

void compute(int i, int j, int k, int l) {
  if (j == n) {
    DP[i][k] += DP[i - 1][l];
    DP[i][k] %= mod;
    return;
  }

  if (k >> j & 1) {
    compute(i, j + 1, k, l);
    return;
  }

  if (j + 1 < n && !(k >> (j + 1) & 1)) {
    compute(i, j + 2, k, l);
  }

  compute(i, j + 1, k, l ^ (1 << j));
}

void solve() {
  cin >> n >> m;

  DP[0][0] = 1;

  rep(i, 1, m + 1) {
    rep(k, 0, 1 << n) { compute(i, 0, k, 0); }
  }

  print(DP[m][0]);
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
