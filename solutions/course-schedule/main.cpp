#include <iostream>
#include <queue>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

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

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n);
  while (m--) {
    int a, b;
    std::cin >> a >> b;

    graph[a - 1].push_back(b - 1);
  }

  const auto vertices = TopologicalSort(graph);

  if (vertices.empty()) {
    std::cout << "IMPOSSIBLE\n";
  } else {
    for (auto u : vertices) {
      std::cout << u + 1 << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
