#include <iostream>
#include <string>
#include <vector>

void dfs(int i, int j, int n, int m, const std::vector<std::string> &grid,
         std::vector<std::vector<bool>> *visited) {
  static const std::vector<std::pair<int, int>> directions{
      {-1, 0}, {1, 0}, {0, 1}, {0, -1}};

  (*visited)[i][j] = true;

  for (const auto &[di, dj] : directions) {
    int r = i + di, c = j + dj;
    if (r >= 0 && r < n && c >= 0 && c < m && !(*visited)[r][c] &&
        grid[r][c] == '.') {
      dfs(r, c, n, m, grid, visited);
    }
  }
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> grid(n);
  for (auto &row : grid) {
    std::cin >> row;
  }

  std::vector visited(n, std::vector<bool>(m));

  int components = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == '.' && !visited[i][j]) {
        ++components;
        dfs(i, j, n, m, grid, &visited);
      }
    }
  }

  std::cout << components << "\n";

  return 0;
}
