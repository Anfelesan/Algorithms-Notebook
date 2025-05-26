// Requires the definition of the modulo MOD and
// the function inv() to compute the multiplicative inverse modulo MOD

struct Comb {
  vector<ll> _fact = vector<ll>(1, 1LL);
  vector<ll> _invfact = vector<ll>(1, 1LL);
 
  ll fact(int x) {
    while (_fact.size() - 1 < x) {
      _fact.push_back((_fact.back() * _fact.size()) % MOD);
      _invfact.push_back(inv(_fact.back()));
    }
    return _fact[x];
  }
  ll invfact(int x) {
    fact(x);
    return _invfact[x];
  }
  ll binom(int n, int k) {
    return (((fact(n) * invfact(k)) % MOD) * invfact(n - k)) % MOD;
  }
} comb;
