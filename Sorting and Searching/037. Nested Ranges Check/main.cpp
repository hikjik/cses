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

bool comp(const pair<pii, int> &left, const pair<pii, int> &right) {
  return forward_as_tuple(left.ff.ff, -left.ff.ss, left.ss) <
         forward_as_tuple(right.ff.ff, -right.ff.ss, right.ss);
}

void solve() {
  int n;
  cin >> n;

  vector<pair<pii, int>> arr;
  arr.reserve(n);
  rep(i, 0, n) {
    int a, b;
    cin >> a >> b;
    arr.pb({{a, b}, i});
  }

  sort(all(arr), comp);

  vi contained(n, 0);
  vi contains(n, 0);

  int max_right = 0;
  rep(i, 0, n) {
    if (arr[i].ff.ss <= max_right) {
      contained[arr[i].ss] = 1;
    }
    max_right = max(max_right, arr[i].ff.ss);
  }

  int min_right = 1e9 + 1;
  repr(i, n - 1, 0) {
    if (arr[i].ff.ss >= min_right) {
      contains[arr[i].ss] = 1;
    }
    min_right = min(min_right, arr[i].ff.ss);
  }

  rep(i, 0, n) { cout << contains[i] << " "; }
  print("");

  rep(i, 0, n) { cout << contained[i] << " "; }
  print("");
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
