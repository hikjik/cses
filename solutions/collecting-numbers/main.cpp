#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<int> index(n + 1);
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;

    index[a] = i;
  }

  int rounds = 1;
  for (int i = 1; i <= n; ++i) {
    if (index[i] < index[i - 1]) {
      ++rounds;
    }
  }

  std::cout << rounds << "\n";

  return 0;
}
