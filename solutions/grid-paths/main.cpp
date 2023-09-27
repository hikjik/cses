#include <iostream>
#include <string>

const int kGridSize = 7;
bool grid[kGridSize + 2][kGridSize + 2];

int CountGridPaths(size_t i, size_t j, size_t k,
                   const std::string &description) {
  if (grid[i][j]) {
    return 0;
  }
  if (grid[i][j - 1] && grid[i][j + 1] && !grid[i - 1][j] && !grid[i + 1][j]) {
    return 0;
  }
  if (grid[i - 1][j] && grid[i + 1][j] && !grid[i][j - 1] && !grid[i][j + 1]) {
    return 0;
  }
  if (i == kGridSize && j == 1) {
    return k == description.size();
  }
  if (k == description.size()) {
    return 0;
  }

  int cnt = 0;
  grid[i][j] = true;
  if (description[k] == 'L' || description[k] == '?') {
    cnt += CountGridPaths(i, j - 1, k + 1, description);
  }
  if (description[k] == 'R' || description[k] == '?') {
    cnt += CountGridPaths(i, j + 1, k + 1, description);
  }
  if (description[k] == 'U' || description[k] == '?') {
    cnt += CountGridPaths(i - 1, j, k + 1, description);
  }
  if (description[k] == 'D' || description[k] == '?') {
    cnt += CountGridPaths(i + 1, j, k + 1, description);
  }
  grid[i][j] = false;
  return cnt;
}

int CountGridPaths(const std::string &description) {
  for (size_t i = 0; i < kGridSize + 2; ++i) {
    grid[i][0] = grid[i][kGridSize + 1] = true;
    grid[0][i] = grid[kGridSize + 1][i] = true;
  }
  return CountGridPaths(1, 1, 0, description);
}

int main() {
  std::string description;
  std::cin >> description;

  std::cout << CountGridPaths(description) << "\n";
  return 0;
}
