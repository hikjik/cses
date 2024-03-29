#include <iostream>

int FastPower(int a, int b, int m) {
  long long res = 1;
  long long x = a;

  while (b) {
    if (b & 1) {
      res = (res * x) % m;
    }
    x = (x * x) % m;
    b >>= 1;
  }

  return res;
}

void FastIO() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr), std::cout.tie(nullptr);
}

int main() {
  FastIO();

  const int kMod = 1e9 + 7;

  int n;
  std::cin >> n;

  while (n--) {
    int a, b;
    std::cin >> a >> b;

    std::cout << FastPower(a, b, kMod) << "\n";
  }

  return 0;
}
