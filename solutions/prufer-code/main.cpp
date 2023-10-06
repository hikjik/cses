#include <iostream>
#include <queue>
#include <vector>

std::vector<std::pair<int, int>>
ConvertPruferCodeToTree(const std::vector<int> &code) {
  const int vertex_count = code.size() + 2;

  std::vector<int> degree(vertex_count + 1, 1);
  for (auto c : code) {
    ++degree[c];
  }

  std::priority_queue<int, std::vector<int>, std::greater<int>> queue;
  for (int i = 1; i <= vertex_count; ++i) {
    if (degree[i] == 1) {
      queue.push(i);
    }
  }

  std::vector<std::pair<int, int>> edges;
  edges.reserve(vertex_count - 1);

  for (auto c : code) {
    edges.emplace_back(c, queue.top());
    queue.pop();
    if (--degree[c] == 1) {
      queue.push(c);
    }
  }
  const auto c = queue.top();
  queue.pop();
  edges.emplace_back(c, queue.top());

  return edges;
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n;
  std::cin >> n;

  std::vector<int> code(n - 2);
  for (auto &c : code) {
    std::cin >> c;
  }

  const auto edges = ConvertPruferCodeToTree(code);

  for (const auto &[a, b] : edges) {
    std::cout << a << " " << b << "\n";
  }

  return 0;
}
