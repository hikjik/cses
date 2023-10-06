#include <iostream>
#include <optional>
#include <stack>
#include <unordered_set>
#include <vector>

using Graph = std::vector<std::vector<int>>;

std::optional<std::vector<int>> ConstructEulerianCircuit(int source,
                                                         const Graph &graph) {
  for (size_t u = 0; u < graph.size(); ++u) {
    if (graph[u].size() & 1) {
      return std::nullopt;
    }
  }

  std::vector<std::unordered_set<int>> adj_lists(graph.size());
  for (size_t u = 0; u < graph.size(); ++u) {
    adj_lists[u].insert(graph[u].begin(), graph[u].end());
  }

  std::stack<int> stack{{source}};
  std::vector<int> circuit;
  while (!stack.empty()) {
    const auto u = stack.top();
    if (adj_lists[u].empty()) {
      circuit.push_back(u);
      stack.pop();
    } else {
      const auto v = *adj_lists[u].begin();

      adj_lists[u].erase(v);
      adj_lists[v].erase(u);

      stack.push(v);
    }
  }

  for (size_t u = 0; u < adj_lists.size(); ++u) {
    if (!adj_lists[u].empty()) {
      return std::nullopt;
    }
  }

  return circuit;
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
    graph[b - 1].push_back(a - 1);
  }

  const auto circuit = ConstructEulerianCircuit(0, graph);

  if (!circuit) {
    std::cout << "IMPOSSIBLE";
  } else {
    for (auto a : *circuit) {
      std::cout << a + 1 << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
