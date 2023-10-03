#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

using WeightedGraph = std::vector<std::vector<std::pair<int, int>>>;

struct RouteData {
  long long price = 0x3f3f3f3f3f3f3f3f;
  int count = 1;
  int min_length = 0;
  int max_length = 0;
};

RouteData FindMinPriceRoute(int source, int target,
                            const WeightedGraph &graph) {
  static const int kMod = 1e9 + 7;

  const int n = graph.size();

  std::vector<RouteData> dp(n);
  dp[source].price = 0;

  std::vector<bool> visited(n);

  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>, std::greater<>>
      min_heap;
  min_heap.push({0, source});

  while (!min_heap.empty()) {
    const auto [_, u] = min_heap.top();
    min_heap.pop();

    if (visited[u]) {
      continue;
    }
    visited[u] = true;

    for (const auto &[v, w] : graph[u]) {
      if (dp[v].price > dp[u].price + w) {
        dp[v].price = dp[u].price + w;
        dp[v].count = dp[u].count;
        dp[v].min_length = dp[u].min_length + 1;
        dp[v].max_length = dp[u].max_length + 1;

        min_heap.push({dp[v].price, v});
      } else if (dp[v].price == dp[u].price + w) {
        dp[v].count = (dp[v].count + dp[u].count) % kMod;
        dp[v].min_length = std::min(dp[v].min_length, dp[u].min_length + 1);
        dp[v].max_length = std::max(dp[v].max_length, dp[u].max_length + 1);
      }
    }
  }

  return dp[target];
}

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;

  WeightedGraph graph(n);
  while (m--) {
    int a, b, w;
    std::cin >> a >> b >> w;

    graph[a - 1].push_back({b - 1, w});
  }

  const auto [price, count, min_length, max_length] =
      FindMinPriceRoute(0, n - 1, graph);
  std::cout << price << " " << count << " " << min_length << " " << max_length
            << "\n";

  return 0;
}
