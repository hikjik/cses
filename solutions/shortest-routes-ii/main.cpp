#include <algorithm>
#include <iostream>
#include <vector>

using WeightedGraph = std::vector<std::vector<std::pair<int, int>>>;

// Floyd–Warshall algorithm
std::vector<std::vector<long long>> Distances(const WeightedGraph &graph) {
  static const long long kInf = 0x3f3f3f3f3f3f3f3f;
  const int n = graph.size();

  std::vector distances(n, std::vector<long long>(n, kInf));
  for (int u = 0; u < n; ++u) {
    distances[u][u] = 0;
    for (auto [v, w] : graph[u]) {
      distances[u][v] = std::min(distances[u][v], w * 1LL);
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int u = 0; u < n; ++u) {
      for (int v = 0; v < n; ++v) {
        distances[u][v] =
            std::min(distances[u][v], distances[u][k] + distances[k][v]);
      }
    }
  }

  for (int u = 0; u < n; ++u) {
    for (int v = 0; v < n; ++v) {
      if (distances[u][v] == kInf) {
        distances[u][v] = -1;
      }
    }
  }

  return distances;
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m, q;
  std::cin >> n >> m >> q;

  WeightedGraph graph(n);
  while (m--) {
    int a, b, w;
    std::cin >> a >> b >> w;
    --a, --b;

    graph[a].push_back({b, w});
    graph[b].push_back({a, w});
  }

  const auto distances = Distances(graph);

  while (q--) {
    int a, b;
    std::cin >> a >> b;
    --a, --b;

    std::cout << distances[a][b] << "\n";
  }

  return 0;
}
