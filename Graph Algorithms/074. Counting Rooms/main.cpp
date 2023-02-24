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

int visited[1000][1000];
int n, m;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void dfs(const vector<string> &grid, int i, int j) {
  visited[i][j] = 1;

  for (const auto &direction : directions) {
    int k = i + direction[0];
    int l = j + direction[1];
    if (k >= 0 && k < n && l >= 0 && l < m && !visited[k][l] &&
        grid[k][l] == '.') {
      dfs(grid, k, l);
    }
  }
}

void solve() {
  cin >> n >> m;

  vector<string> grid;
  grid.reserve(n);
  rep(i, 0, n) {
    string row;
    cin >> row;
    grid.pb(row);
  }

  memset(visited, 0, sizeof(visited));

  int components = 0;
  rep(i, 0, n) {
    rep(j, 0, m) {
      if (grid[i][j] == '.' && !visited[i][j]) {
        components++;
        dfs(grid, i, j);
      }
    }
  }

  print(components);
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
