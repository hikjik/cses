#include <iostream>
#include <vector>

void DepthFirstSearch(int u, const std::vector<std::vector<int>> &graph,
                      std::vector<int> *subtree_size) {
  (*subtree_size)[u] = 1;
  for (auto v : graph[u]) {
    DepthFirstSearch(v, graph, subtree_size);
    (*subtree_size)[u] += (*subtree_size)[v];
  }
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> graph(n);
  for (int i = 1; i < n; ++i) {
    int u;
    std::cin >> u;

    graph[u - 1].push_back(i);
  }

  std::vector<int> subtree_size(n);
  DepthFirstSearch(0, graph, &subtree_size);

  for (auto s : subtree_size) {
    std::cout << s - 1 << " ";
  }
  std::cout << "\n";

  return 0;
}
