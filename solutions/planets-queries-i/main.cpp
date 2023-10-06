#include <iostream>
#include <vector>

class SuccessorGraph {
private:
  const int kLogMaxSteps = 30;

  std::vector<std::vector<int>> successors_;

public:
  SuccessorGraph(int n, const std::vector<int> &destinations)
      : successors_(kLogMaxSteps, std::vector<int>(n)) {
    successors_[0] = destinations;

    for (int i = 1; i < kLogMaxSteps; ++i) {
      for (int u = 0; u < n; ++u) {
        successors_[i][u] = successors_[i - 1][successors_[i - 1][u]];
      }
    }
  }

  int Advance(int source, int steps) const {
    auto x = source;
    for (int i = 0; i < kLogMaxSteps; ++i) {
      if ((steps >> i) & 1) {
        x = successors_[i][x];
      }
    }
    return x;
  }
};

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, q;
  std::cin >> n >> q;

  std::vector<int> destinations(n);
  for (auto &a : destinations) {
    std::cin >> a;
    --a;
  }

  auto graph = SuccessorGraph(n, destinations);

  while (q--) {
    int x, k;
    std::cin >> x >> k;

    std::cout << graph.Advance(x - 1, k) + 1 << "\n";
  }

  return 0;
}
