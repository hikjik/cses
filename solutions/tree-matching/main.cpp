#include <algorithm>
#include <iostream>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

using Graph = std::vector<std::vector<int>>;

void DepthFirstSearch(int u, int p, const Graph &graph,
                      std::vector<bool> *used) {
  for (auto v : graph[u]) {
    if (v != p) {
      DepthFirstSearch(v, u, graph, used);

      if (!(*used)[u] && !(*used)[v]) {
        (*used)[u] = (*used)[v] = true;
      }
    }
  }
}

int CountTreeMatching(const Graph &graph) {
  std::vector<bool> used(graph.size());
  DepthFirstSearch(0, -1, graph, &used);
  return std::count(used.begin(), used.end(), true) / 2;
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    std::cin >> a >> b;
    --a, --b;

    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  std::cout << CountTreeMatching(graph) << "\n";

  return 0;
}
