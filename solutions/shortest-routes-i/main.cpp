#include <iostream>
#include <queue>
#include <vector>

using WeightedGraph = std::vector<std::vector<std::pair<int, int>>>;

// Dijkstra’s algorithm
std::vector<long long> Distances(int source, const WeightedGraph &graph) {
  static const long long kInf = 0x3f3f3f3f3f3f3f3f;
  const int n = graph.size();

  std::vector<long long> distances(n, kInf);
  distances[source] = 0;

  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>, std::greater<>>
      min_heap;
  min_heap.push({0, source});

  std::vector<bool> visited(n);

  while (!min_heap.empty()) {
    const auto [_, u] = min_heap.top();
    min_heap.pop();

    if (visited[u]) {
      continue;
    }
    visited[u] = true;

    for (const auto &[v, w] : graph[u]) {
      if (distances[u] + w < distances[v]) {
        distances[v] = distances[u] + w;
        min_heap.push({distances[v], v});
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

  int n, m;
  std::cin >> n >> m;

  WeightedGraph graph(n);
  while (m--) {
    int a, b, w;
    std::cin >> a >> b >> w;
    --a, --b;

    graph[a].push_back({b, w});
  }

  for (auto distance : Distances(0, graph)) {
    std::cout << distance << " ";
  }
  std::cout << "\n";

  return 0;
}
