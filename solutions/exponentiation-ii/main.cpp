#include <iostream>

void fast_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
}

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

int main() {
  fast_io();

  const int kMod = 1e9 + 7;

  int n;
  std::cin >> n;

  while (n--) {
    int a, b, c;
    std::cin >> a >> b >> c;

    std::cout << FastPower(a, FastPower(b, c, kMod - 1), kMod) << "\n";
  }

  return 0;
}
