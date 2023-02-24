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

  int visited[n][m];
  pii start;
  pii end;

  for (int i = 0; i < n; i++) {
    string row;
    cin >> row;
    for (int j = 0; j < m; j++) {
      char symbol = row[j];

      if (symbol == '#') {
        visited[i][j] = 1;
      } else {
        visited[i][j] = 0;
        if (symbol == 'A') {
          start = {i, j};
        }
        if (symbol == 'B') {
          end = {i, j};
        }
      }
    }
  }

  vector<tuple<int, int, char>> directions = {
      {-1, 0, 'U'}, {1, 0, 'D'}, {0, 1, 'R'}, {0, -1, 'L'}};

  int dist[n][m];
  char moves[n][m];

  queue<pii> q;
  q.push(start);
  visited[start.ff][start.ss] = 1;
  dist[start.ff][start.ss] = 0;
  while (!q.empty()) {
    pii pos = q.front();
    q.pop();

    for (const auto &direction : directions) {
      int i, j;
      char p;
      tie(i, j, p) = direction;

      int k = pos.ff + i;
      int l = pos.ss + j;
      if (k >= 0 && k < n && l >= 0 && l < m && !visited[k][l]) {
        visited[k][l] = 1;
        dist[k][l] = dist[pos.ff][pos.ss] + 1;
        moves[k][l] = p;
        q.emplace(k, l);
      }
    }
  }

  if (!visited[end.ff][end.ss]) {
    print("NO");
    return;
  }

  print("YES");
  print(dist[end.ff][end.ss]);

  string path(dist[end.ff][end.ss], '*');
  repr(i, dist[end.ff][end.ss] - 1, 0) {
    path[i] = moves[end.ff][end.ss];
    switch (moves[end.ff][end.ss]) {
    case 'D':
      end = {end.ff - 1, end.ss};
      break;
    case 'U':
      end = {end.ff + 1, end.ss};
      break;
    case 'L':
      end = {end.ff, end.ss + 1};
      break;
    case 'R':
      end = {end.ff, end.ss - 1};
      break;
    default:
      assert(false && "Unreachable");
    }
  }
  print(path);
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
