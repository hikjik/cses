#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

std::vector<std::vector<int>> BuildDeBruijnGraph(int m) {
  const int n = 1 << (m - 1);

  std::vector<std::vector<int>> graph(n);
  for (int u = 0; u < n; ++u) {
    const auto v = (u << 1) % n;
    graph[u].push_back(v);
    graph[u].push_back(v | 1);
  }

  return graph;
}

std::string BuildDeBruijnSequence(int n) {
  if (n == 1) {
    return "01";
  }

  auto graph = BuildDeBruijnGraph(n);
  std::stack<int> stack{{0}};
  std::vector<int> circuit;
  while (!stack.empty()) {
    const auto u = stack.top();
    if (graph[u].empty()) {
      circuit.push_back(u);
      stack.pop();
    } else {
      const auto v = graph[u].back();
      graph[u].pop_back();
      stack.push(v);
    }
  }

  std::stringstream ss;
  for (auto a : circuit) {
    ss << (a & 1);
  }
  ss << std::string(n - 2, '0');
  return ss.str();
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  std::cout << BuildDeBruijnSequence(n) << "\n";

  return 0;
}
