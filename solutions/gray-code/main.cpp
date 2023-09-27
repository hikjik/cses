#include <iostream>

void PrintBinary(int number, int n) {
  for (int i = n - 1; i >= 0; --i) {
    std::cout << ((number >> i) & 1);
  }
  std::cout << "\n";
}

int main() {
  int n;
  std::cin >> n;

  for (int i = 0; i < (1 << n); ++i) {
    PrintBinary(i ^ (i >> 1), n);
  }

  return 0;
}
