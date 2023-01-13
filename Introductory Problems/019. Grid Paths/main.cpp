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

const int GRID_SIZE = 9;
bool grid[GRID_SIZE][GRID_SIZE];

const int PATH_LENGTH = 48;
int path[PATH_LENGTH];

int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};
int total = 0;

void count_paths(int i, int j, int step) {
  if (grid[i][j] == true) {
    return;
  }

  if (grid[i][j - 1] && grid[i][j + 1] && !grid[i - 1][j] && !grid[i + 1][j]) {
    return;
  }

  if (grid[i - 1][j] && grid[i + 1][j] && !grid[i][j - 1] && !grid[i][j + 1]) {
    return;
  }

  if (i == 7 && j == 1) {
    if (step == PATH_LENGTH) {
      total++;
    };
    return;
  }

  if (step == PATH_LENGTH) {
    return;
  };

  grid[i][j] = true;

  int k = path[step];
  if (k < 4) {
    count_paths(i + dr[k], j + dc[k], step + 1);
  } else {
    rep(k, 0, 4) { count_paths(i + dr[k], j + dc[k], step + 1); }
  }

  grid[i][j] = false;
}

void solve() {
  rep(i, 0, GRID_SIZE) {
    grid[i][0] = grid[i][8] = grid[0][i] = grid[8][i] = true;
  }

  rep(i, 1, GRID_SIZE - 1) {
    rep(j, 1, GRID_SIZE - 1) { grid[i][j] = false; }
  }

  string p;
  cin >> p;
  rep(i, 0, PATH_LENGTH) {
    if (p[i] == 'L') {
      path[i] = 0;
    } else if (p[i] == 'R') {
      path[i] = 1;
    } else if (p[i] == 'U') {
      path[i] = 2;
    } else if (p[i] == 'D') {
      path[i] = 3;
    } else {
      path[i] = 4;
    }
  }
  count_paths(1, 1, 0);
  print(total);
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
