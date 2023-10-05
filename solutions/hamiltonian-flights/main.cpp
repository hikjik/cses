#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

const int kMod = 1e9 + 7;

int CountHamiltonianPath(const std::vector<std::vector<int>> &revered_graph) {
  const int n = revered_graph.size();
  const int src = 0, dst = n - 1;

  std::vector dp(n, std::vector<int>(1 << n));
  dp[src][1 << src] = 1;
  for (int mask = 2; mask < 1 << n; ++mask) {
    if (!(mask & (1 << src))) {
      continue;
    }
    if ((mask & (1 << dst)) && mask != (1 << n) - 1) {
      continue;
    }

    for (int v = 0; v < n; ++v) {
      if (!(mask & (1 << v))) {
        continue;
      }

      for (auto u : revered_graph[v]) {
        if ((mask & (1 << u))) {
          dp[v][mask] = (dp[v][mask] + dp[u][mask ^ (1 << v)]) % kMod;
        }
      }
    }
  }

  return dp[dst][(1 << n) - 1];
}

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> revered_graph(n);
  while (m--) {
    int a, b;
    std::cin >> a >> b;

    revered_graph[b - 1].push_back(a - 1);
  }

  std::cout << CountHamiltonianPath(revered_graph) << "\n";

  return 0;
}
