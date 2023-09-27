#include <iostream>

void TowerOfHanoi(int from, int to, int depth) {
  if (depth) {
    const auto aux = 6 - from - to;

    TowerOfHanoi(from, aux, depth - 1);
    std::cout << from << " " << to << "\n";
    TowerOfHanoi(aux, to, depth - 1);
  }
}

int main() {
  int n;
  std::cin >> n;

  std::cout << ((1 << n) - 1) << "\n";
  TowerOfHanoi(1, 3, n);

  return 0;
}
