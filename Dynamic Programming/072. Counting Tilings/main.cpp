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

  int pow_n = (1 << n);

  vector<vector<int>> cp(pow_n, vector<int>(pow_n, 0));
  rep(i, 0, pow_n) {
    rep(j, 0, pow_n) {
      cp[i][j] = 1;
      rep(k, 0, n) {
        if ((i >> k & 1) && (j >> k & 1)) {
          cp[i][j] = 0;
          break;
        }

        if (!(i >> k & 1) && !(j >> k & 1)) {
          if (k + 1 < n && !(i >> (k + 1) & 1) && !(j >> (k + 1) & 1)) {
            k++;
            continue;
          }
          cp[i][j] = 0;
          break;
        }
      }
    }
  }

  // dp[j][i] - number of ways to fully cover first j−1 columns and have a
  // mask i on the jth column where every set bit in i corresponds to an already
  // occupied cell and unset bit to unoccupied cells.
  vector<vector<int>> dp(m + 1, vector<int>(pow_n, 0));
  dp[0][0] = 1;
  rep(j, 1, m + 1) {
    rep(i, 0, pow_n) {
      rep(k, 0, pow_n) {
        dp[j][i] += cp[k][i] * dp[j - 1][k];
        dp[j][i] %= mod;
      }
    }
  }
  print(dp[m][0]);
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
