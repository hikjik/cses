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
  int n, x;
  cin >> n >> x;

  vector<pii> arr;
  arr.reserve(n);
  rep(i, 0, n) {
    int a;
    cin >> a;
    arr.emplace_back(a, i);
  }
  sort(all(arr));

  rep(i, 0, n) {
    int target = x - arr[i].ff;

    int l = 0;
    int r = n - 1;
    while (l < r) {
      int sum = arr[l].ff + arr[r].ff;
      if (l != i && r != i && sum == target) {
        print3(arr[i].ss + 1, arr[l].ss + 1, arr[r].ss + 1);
        return;
      } else {
        if (sum < target) {
          l++;
        } else {
          r--;
        }
      }
    }
  }

  print("IMPOSSIBLE")
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
