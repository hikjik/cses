#include <iostream>
#include <queue>
#include <vector>

std::vector<int> TopologicalSort(const std::vector<std::vector<int>> &graph) {
  const int n = graph.size();

  std::vector<int> in_degree(n);
  for (int u = 0; u < n; ++u) {
    for (auto v : graph[u]) {
      ++in_degree[v];
    }
  }

  std::queue<int> queue;
  for (int u = 0; u < n; ++u) {
    if (!in_degree[u]) {
      queue.push(u);
    }
  }

  std::vector<int> vertices;
  while (!queue.empty()) {
    const auto u = queue.front();
    queue.pop();

    vertices.push_back(u);
    for (auto v : graph[u]) {
      if (!--in_degree[v]) {
        queue.push(v);
      }
    }
  }

  if (vertices.size() != graph.size()) {
    return {};
  }
  return vertices;
}

int CountGameRoutes(int source, int target,
                    const std::vector<std::vector<int>> &graph) {
  static const int kMod = 1e9 + 7;

  std::vector<int> distances(graph.size());
  distances[source] = 1;

  for (auto u : TopologicalSort(graph)) {
    for (auto v : graph[u]) {
      distances[v] = (distances[v] + distances[u]) % kMod;
    }
  }

  return distances[target];
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n);
  while (m--) {
    int a, b;
    std::cin >> a >> b;

    graph[a - 1].push_back(b - 1);
  }

  std::cout << CountGameRoutes(0, n - 1, graph) << "\n";

  return 0;
}
