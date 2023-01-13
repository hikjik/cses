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

vector<string> board;
array<int, 8> col;
array<int, 8 * 2 - 1> diag1;
array<int, 8 * 2 - 1> diag2;
int total = 0;

void count_queens(int i) {
  if (i == 8) {
    total++;
    return;
  }

  rep(j, 0, 8) {
    if (board[i][j] == '.' && col[j] == 0 && diag1[i + j] == 0 &&
        diag2[i + 7 - j] == 0) {
      col[j] = diag1[i + j] = diag2[i + 7 - j] = 1;
      count_queens(i + 1);
      col[j] = diag1[i + j] = diag2[i + 7 - j] = 0;
    }
  }
}

void solve() {
  rep(i, 0, 8) {
    string s;
    cin >> s;
    board.push_back(s);
  }

  count_queens(0);
  print(total);
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}