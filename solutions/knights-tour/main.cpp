#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <tuple>

const int kN = 8;
using Board = std::array<std::array<int, kN>, kN>;

const std::array<std::pair<int, int>, 8> kKnightMoves{
    {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {2, 1}, {2, -1}, {1, 2}, {1, -2}}};

bool IsFree(int x, int y, const Board *board) {
  return 0 <= x && x < kN && 0 <= y && y < kN && !(*board)[x][y];
}

int Degree(int x, int y, const Board *board) {
  int degree = 0;
  for (const auto &[dx, dy] : kKnightMoves) {
    if (IsFree(x + dx, y + dy, board)) {
      ++degree;
    }
  }
  return degree;
}

bool KnightTour(int step, int x, int y, Board *board) {
  (*board)[x][y] = step + 1;
  if (step == kN * kN - 1) {
    return true;
  }

  std::vector<std::tuple<int, int, int>> next;
  for (const auto &[dx, dy] : kKnightMoves) {
    const auto i = x + dx, j = y + dy;
    if (IsFree(i, j, board)) {
      next.push_back({Degree(i, j, board), i, j});
    }
  }
  std::sort(next.begin(), next.end());

  for (const auto &[_, i, j] : next) {
    if (KnightTour(step + 1, i, j, board)) {
      return true;
    }
  }

  (*board)[x][y] = 0;
  return false;
}

Board KnightTour(int x, int y) {
  Board board{};
  KnightTour(0, x, y, &board);
  return board;
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  int x, y;
  std::cin >> x >> y;

  for (const auto &row : KnightTour(y - 1, x - 1)) {
    for (auto a : row) {
      std::cout << std::setw(2) << a << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
