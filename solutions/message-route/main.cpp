#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> graph(n + 1);
  while (m--) {
    int a, b;
    std::cin >> a >> b;

    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  const int source = 1, target = n;
  std::unordered_map<int, int> predecessors{{source, -1}};
  std::queue<int> queue{{source}};
  while (!queue.empty() && !predecessors.contains(target)) {
    const auto u = queue.front();
    queue.pop();

    for (auto v : graph[u]) {
      if (predecessors.contains(v)) {
        continue;
      }
      queue.push(v);
      predecessors[v] = u;

      if (v == target) {
        break;
      }
    }
  }

  if (!predecessors.contains(target)) {
    std::cout << "IMPOSSIBLE\n";
    return 0;
  }

  std::vector<int> route;
  for (int v = target; v != -1; v = predecessors[v]) {
    route.push_back(v);
  }

  std::cout << route.size() << "\n";
  for (int i = route.size() - 1; i >= 0; --i) {
    std::cout << route[i] << " ";
  }
  std::cout << "\n";

  return 0;
}
