#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

int MinimumNumbersOfMoves(const std::string &source,
                          const std::string &target) {
  static const std::vector<std::pair<int, int>> swaps{
      {0, 1}, {1, 2}, {3, 4}, {4, 5}, {6, 7}, {7, 8}, // horizontal
      {0, 3}, {1, 4}, {2, 5}, {3, 6}, {4, 7}, {5, 8}, // vertical
  };

  if (source == target) {
    return 0;
  }

  std::unordered_set<std::string> visited{{source}};
  std::queue<std::string> queue{{source}};
  for (int steps = 1; !queue.empty(); ++steps) {
    for (int sz = queue.size(); sz; --sz) {
      auto grid = queue.front();
      queue.pop();

      for (const auto &[i, j] : swaps) {
        std::swap(grid[i], grid[j]);
        if (!visited.contains(grid)) {
          if (grid == target) {
            return steps;
          }
          visited.insert(grid);
          queue.push(grid);
        }
        std::swap(grid[i], grid[j]);
      }
    }
  }

  throw;
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  std::string target = "123456789", source = target;
  for (auto &c : source) {
    std::cin >> c;
  }

  std::cout << MinimumNumbersOfMoves(source, target) << "\n";
  return 0;
}
