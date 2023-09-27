#include <iostream>
#include <string>
#include <tuple>
#include <vector>

const size_t kBoardSize = 8;

class State {
public:
  State()
      : cols(kBoardSize), main_diag(kBoardSize * 2 - 1),
        anti_diag(kBoardSize * 2 - 1) {}

  bool Get(size_t i, size_t j) const {
    return !cols[j] && !main_diag[i + j] && !anti_diag[i + kBoardSize - j - 1];
  }

  void Set(size_t i, size_t j, bool value) {
    cols[j] = main_diag[i + j] = anti_diag[i + kBoardSize - j - 1] = value;
  }

private:
  std::vector<bool> cols;
  std::vector<bool> main_diag;
  std::vector<bool> anti_diag;
};

void CountWaysToPlaceQueens(size_t i, const std::vector<std::string> &board,
                            State *state, int *cnt) {
  if (i == board.size()) {
    ++*cnt;
    return;
  }

  for (size_t j = 0; j < board.size(); ++j) {
    if (board[i][j] == '.' && state->Get(i, j)) {
      state->Set(i, j, true);
      CountWaysToPlaceQueens(i + 1, board, state, cnt);
      state->Set(i, j, false);
    }
  }
}

int CountWaysToPlaceQueens(const std::vector<std::string> &board) {
  State state;
  int cnt = 0;
  CountWaysToPlaceQueens(0, board, &state, &cnt);
  return cnt;
}

int main() {
  std::vector<std::string> board(kBoardSize);
  for (auto &row : board) {
    std::cin >> row;
  }

  std::cout << CountWaysToPlaceQueens(board) << "\n";

  return 0;
}
