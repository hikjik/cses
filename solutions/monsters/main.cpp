#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

bool IsOnBoundary(int i, int j, int n, int m) {
  return i == 0 || i == n - 1 || j == 0 || j == m - 1;
}

std::string BuildRoute(int start_x, int start_y, int end_x, int end_y,
                       const std::vector<std::string> &predecessors) {
  std::string route;
  int x = end_x, y = end_y;
  while (x != start_x || y != start_y) {
    route += predecessors[x][y];
    x += (route.back() == 'U') - (route.back() == 'D');
    y += (route.back() == 'L') - (route.back() == 'R');
  }
  std::reverse(route.begin(), route.end());
  return route;
}

std::optional<std::string>
GetEscapeRoute(const std::vector<std::string> &grid) {
  const int n = grid.size(), m = grid.back().size();

  std::vector visited(n, std::vector<bool>(m));
  std::vector predecessors(n, std::string(m, '-'));

  std::queue<std::tuple<int, int, char>> queue;
  int user_x = 0, user_y = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == '.') {
        continue;
      }
      visited[i][j] = true;
      if (grid[i][j] == 'M') {
        queue.push({i, j, 'M'});
      }
      if (grid[i][j] == 'A') {
        if (IsOnBoundary(i, j, n, m)) {
          return "";
        }
        user_x = i, user_y = j;
      }
    }
  }

  queue.push({user_x, user_y, 'A'});
  while (!queue.empty()) {
    for (int sz = queue.size(); sz > 0; --sz) {
      const auto [i, j, unit] = queue.front();
      queue.pop();

      for (char direction : {'L', 'R', 'D', 'U'}) {
        const int r = i + (direction == 'D') - (direction == 'U');
        const int c = j + (direction == 'R') - (direction == 'L');
        if (r < 0 || r >= n || c < 0 || c >= m || visited[r][c]) {
          continue;
        }

        if (unit == 'A') {
          predecessors[r][c] = direction;
          if (IsOnBoundary(r, c, n, m)) {
            return BuildRoute(user_x, user_y, r, c, predecessors);
          }
        }

        visited[r][c] = true;
        queue.push({r, c, unit});
      }
    }
  }

  return std::nullopt;
}

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> grid(n);
  for (auto &row : grid) {
    std::cin >> row;
  }

  const auto route = GetEscapeRoute(grid);

  if (!route) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    std::cout << route->size() << "\n";
    std::cout << *route << "\n";
  }

  return 0;
}
