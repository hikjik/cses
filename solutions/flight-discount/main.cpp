#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

using Graph = std::vector<std::vector<std::pair<int, int>>>;

long long ComputeMinDistance(int source, int target, const Graph &graph) {
  static const long long kInf = 0x3f3f3f3f3f3f3f3f;
  const int n = graph.size();

  std::vector distances(2, std::vector<long long>(n, kInf));
  distances[0][source] = distances[1][source] = 0;

  std::vector visited(2, std::vector<bool>(n));

  std::priority_queue<std::tuple<long long, int, bool>,
                      std::vector<std::tuple<long long, int, bool>>,
                      std::greater<>>
      min_heap;
  min_heap.emplace(0, source, true);

  while (!min_heap.empty()) {
    const auto [distance, u, coupon] = min_heap.top();
    min_heap.pop();

    if (visited[coupon][u]) {
      continue;
    }
    visited[coupon][u] = true;

    for (const auto &[v, w] : graph[u]) {
      if (distances[coupon][v] > distance + w) {
        distances[coupon][v] = distance + w;
        min_heap.emplace(distances[coupon][v], v, coupon);
      }
      if (coupon) {
        if (distances[!coupon][v] > distance + w / 2) {
          distances[!coupon][v] = distance + w / 2;
          min_heap.emplace(distances[!coupon][v], v, !coupon);
        }
      }
    }
  }

  return std::min(distances[0][target], distances[1][target]);
}

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;
  Graph graph(n);
  while (m--) {
    int a, b, w;
    std::cin >> a >> b >> w;

    graph[a - 1].push_back({b - 1, w});
  }

  std::cout << ComputeMinDistance(0, n - 1, graph) << "\n";

  return 0;
}
