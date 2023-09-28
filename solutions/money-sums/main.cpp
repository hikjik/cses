#include <iostream>
#include <vector>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

int main() {
  fast_io();

  int n;
  std::cin >> n;

  std::vector<int> coins(n);
  int sum = 0;
  for (auto &c : coins) {
    std::cin >> c;
    sum += c;
  }

  std::vector<bool> reachable(sum + 1, 0);
  reachable[0] = true;
  int cnt = 0;
  for (auto c : coins) {
    for (int i = sum; i - c >= 0; --i) {
      if (reachable[i - c]) {
        if (!reachable[i]) {
          ++cnt;
        }
        reachable[i] = true;
      }
    }
  }

  std::cout << cnt << "\n";
  for (int i = 1; i <= sum; ++i) {
    if (reachable[i]) {
      std::cout << i << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
