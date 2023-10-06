#include <iostream>
#include <optional>
#include <stack>
#include <vector>

using Graph = std::vector<std::vector<int>>;

std::optional<std::vector<int>> ConstructEulerianTrail(int src, int dst,
                                                       Graph graph) {
  const int n = graph.size();

  std::vector<int> in_degree(n), out_degree(n);
  for (int u = 0; u < n; ++u) {
    for (auto v : graph[u]) {
      ++in_degree[v], ++out_degree[u];
    }
  }

  for (int u = 0; u < n; ++u) {
    if (in_degree[u] + (u == src) != out_degree[u] + (u == dst)) {
      return std::nullopt;
    }
  }

  std::vector<int> trail;
  std::stack<int> stack{{src}};
  while (!stack.empty()) {
    const auto u = stack.top();
    if (graph[u].empty()) {
      trail.push_back(u);
      stack.pop();
    } else {
      stack.push(graph[u].back());
      graph[u].pop_back();
    }
  }

  for (size_t u = 0; u < graph.size(); ++u) {
    if (!graph[u].empty()) {
      return std::nullopt;
    }
  }

  std::reverse(trail.begin(), trail.end());
  return trail;
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;

    graph[a - 1].push_back(b - 1);
  }

  const auto trail = ConstructEulerianTrail(0, n - 1, std::move(graph));

  if (!trail) {
    std::cout << "IMPOSSIBLE";
  } else {
    for (auto a : *trail) {
      std::cout << a + 1 << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
