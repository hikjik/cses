#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int repetitions = 0;
  char prev = '#';

  int count = 0;
  char c;
  while (cin.get(c)) {
    if (c != prev) {
      repetitions = max(repetitions, count);
      count = 0;
    }
    count++;
    prev = c;
  }
  cout << max(repetitions, count) << "\n";

  return 0;
}
