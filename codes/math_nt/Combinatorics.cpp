namespace Combinatorics {
vector<int> fat;
vector<int> ifat;

void precalculate(int n) {
  fat.resize(n + 1, 1);
  ifat.resize(n + 1, 1);
  for (int i = 1; i <= n; i++) {
    fat[i] = mod(fat[i - 1] * i);
    ifat[i] = exp(fat[i], M - 2);
  }
}

int C(int n, int k) { return mod(mod(fat[n] * ifat[n - k]) * ifat[k]); }
}  // namespace Combinatorics
