// Iterative approach
long long Binexp(long long a, long long b, int mod) {
  long long res = 1LL;
  for (int k = 0; (1LL << k) <= b; ++k) {
    if ((1LL << k) & b) (res *= a) %= mod;
    (a *= a) %= mod;
  }
  return res;
}

// Recursive approach
long long Binexp(long long a, long long b, int mod) {
  if (b == 0) return 1LL;
  if (b == 1) return a % mod;
  long long res = Binexp(a, b / 2LL);
  return (((res * res) % mod) * (b & 1 ? a : 1)) % mod;
}
