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

class CostSet {
public:
  ll cost() {
    ll median = *left.rbegin();
    return median * left.size() - left_sum + right_sum - right.size() * median;
  }

  void insert(int value) {
    if (!left.empty() && value > *left.rbegin()) {
      right.insert(value);
      right_sum += value;
    } else {
      left.insert(value);
      left_sum += value;
    }

    this->rebalance();
  }

  void erase(int value) {
    if (auto it = left.find(value); it != left.end()) {
      left_sum -= *it;
      left.erase(it);
    } else if (auto it = right.find(value); it != right.end()) {
      right_sum -= *it;
      right.erase(it);
    } else {
      assert("Unreachable");
    }

    this->rebalance();
  }

private:
  void rebalance() {
    if (right.size() > left.size()) {
      const int value = *right.begin();
      right_sum -= value;
      left_sum += value;
      right.erase(right.begin());
      left.insert(value);
    } else if (right.size() + 1 < left.size()) {
      const int value = *left.rbegin();
      right_sum += value;
      left_sum -= value;
      left.erase(--left.end());
      right.insert(value);
    } else {
      assert("Unreachable");
    }
  }

  multiset<int> left;
  multiset<int> right;
  ll left_sum = 0;
  ll right_sum = 0;
};

void solve() {
  int n, k;
  cin >> n >> k;

  vi arr(n);
  rep(i, 0, n) { cin >> arr[i]; }

  CostSet cost_set;
  rep(i, 0, k - 1) { cost_set.insert(arr[i]); }

  rep(i, k - 1, n) {
    cost_set.insert(arr[i]);
    cout << cost_set.cost() << " ";
    cost_set.erase(arr[i - k + 1]);
  }
  cout << "\n";
}

int main() {
  fastio();
  online_judge();
  solve();
  return 0;
}
