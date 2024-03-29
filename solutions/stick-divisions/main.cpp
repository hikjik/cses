#include <iostream>
#include <queue>

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int x, n;
  std::cin >> x >> n;

  std::priority_queue<int, std::vector<int>, std::greater<int>> queue;
  while (n--) {
    int d;
    std::cin >> d;

    queue.push(d);
  }

  long long cost = 0;
  while (queue.size() > 1) {
    const auto a = queue.top();
    queue.pop();
    const auto b = queue.top();
    queue.pop();
    cost += a + b;
    queue.push(a + b);
  }

  std::cout << cost << "\n";

  return 0;
}
