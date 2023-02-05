#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

  ordered_set<pii> oset;
  rep(i, 0, n) {
    auto key = pii(arr[i].ff.ss, -i);
    oset.insert(key);
    contained[arr[i].ss] = i - oset.order_of_key(key);
  }

  oset.clear();
  repr(i, n - 1, 0) {
    auto key = pii(arr[i].ff.ss, -i);
    oset.insert(key);
    contains[arr[i].ss] = oset.order_of_key(key);
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
