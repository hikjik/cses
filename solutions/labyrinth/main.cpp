#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int n, m;
  std::cin >> n >> m;

  std::vector visited(n, std::vector<bool>(m));
  std::pair<int, int> start, end;
  for (int i = 0; i < n; i++) {
    std::string row;
    std::cin >> row;

    for (int j = 0; j < m; j++) {
      switch (row[j]) {
      case '#':
        visited[i][j] = true;
        break;
      case 'A':
        visited[i][j] = true;
        start = {i, j};
        break;
      case 'B':
        end = {i, j};
        break;
      }
    }
  }

  const std::vector<std::tuple<int, int, char>> directions{
      std::make_tuple(-1, 0, 'U'),
      std::make_tuple(1, 0, 'D'),
      std::make_tuple(0, 1, 'R'),
      std::make_tuple(0, -1, 'L'),
  };

  std::vector dist(n, std::vector<int>(m));
  std::vector moves(n, std::vector<char>(m));

  std::queue<std::pair<int, int>> queue;
  queue.push(start);
  while (!queue.empty()) {
    const auto [i, j] = queue.front();
    queue.pop();

    for (const auto &[di, dj, p] : directions) {
      const auto r = i + di, c = j + dj;
      if (r >= 0 && r < n && c >= 0 && c < m && !visited[r][c]) {
        visited[r][c] = 1;
        dist[r][c] = dist[i][j] + 1;
        moves[r][c] = p;
        queue.emplace(r, c);
      }
    }
  }

  if (!visited[end.first][end.second]) {
    std::cout << "NO\n";
    return 0;
  }

  std::cout << "YES\n";
  std::cout << dist[end.first][end.second] << "\n";

  std::string path(dist[end.first][end.second], '*');
  for (int i = dist[end.first][end.second] - 1; i >= 0; --i) {
    path[i] = moves[end.first][end.second];
    switch (path[i]) {
    case 'D':
      end = {end.first - 1, end.second};
      break;
    case 'U':
      end = {end.first + 1, end.second};
      break;
    case 'L':
      end = {end.first, end.second + 1};
      break;
    case 'R':
      end = {end.first, end.second - 1};
      break;
    }
  }
  std::cout << path << "\n";

  return 0;
}
