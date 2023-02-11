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
  int n;
  cin >> n;

  vi coins(n);
  int sum = 0;
  rep(i, 0, n) {
    cin >> coins[i];
    sum += coins[i];
  }

  vi reachable(sum + 1, 0);
  reachable[0] = 1;
  int total = 0;
  for (auto c : coins) {
    for (int i = sum; i - c >= 0; --i) {
      if (reachable[i - c]) {
        if (!reachable[i]) {
          total++;
        }
        reachable[i] = 1;
      }
    }
  }

  cout << total << endl;
  rep(i, 1, sum + 1) {
    if (reachable[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
