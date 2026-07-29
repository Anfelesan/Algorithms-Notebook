// Tested on: https://codeforces.com/contest/2143/submission/384702958
// Building complexity: O(|arr|*LOG)
// GetBasis, Kth and Order Complexity: O(LOG)
// Kth, Order are 0-indexed
//
// T depends on size of LOG: may be int, long long
template<typename T, int LOG>
struct XorBasis {
  vector<array<T, LOG>> basis; // Suffix basis
  vector<array<int, LOG>> time;
  XorBasis(vector<T>& arr) {
    const int n = arr.size();
    basis = vector<array<T, LOG>>(n);
    time = vector<array<int, LOG>>(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < LOG; ++j) {
        basis[i][j] = T(0);
        time[i][j] = INT_MAX;
      }
    }
    for (int i = n - 1; i >= 0; --i) {
      if (i + 1 < n) {
        basis[i] = basis[i + 1];
        time[i] = time[i + 1];
      }
      Add(arr[i], i);
    }
  }
  void Add(T x, int idx) {
    int xtime = idx;
    for (int k = LOG - 1; k >= 0; --k) {
      if ((T(1) << k) & x) {
        if (time[idx][k] > xtime) {
          swap(time[idx][k], xtime);
          swap(basis[idx][k], x);
        }
        x ^= basis[idx][k];
      }
    }
  }

  // pair<basis, idxs>
  pair<array<T, LOG>, array<int, LOG>> GetBasis(int l, int r) {
    array<T, LOG> b; array<int, LOG> t;
    for (int k = LOG - 1; k >= 0; --k) {
      b[k] = 0, t[k] = -1;
      if (time[l][k] <= r) {
        b[k] = basis[l][k];
        t[k] = time[l][k];
      }
    }
    return { b, t };
  }
  T Kth(T kth, const array<T, LOG>& basis) {
    array<bool, LOG> rf;
    int cb = 0;
    for (int k = 0; k < LOG; ++k) {
      if (basis[k] > T(0)) {
        rf[k] = bool(kth & (T(1) << cb));
        ++cb;
      }
    }
    assert((kth >> cb) == T(0)); // kth < |span|
    T res = 0;
    for (int k = LOG - 1; k >= 0; --k) {
      if (basis[k] > T(0)) {
        res = rf[k] ? max(res, res ^ basis[k]) : min(res, res ^ basis[k]);
      }
    }
    return res;
  }
  pair<T, bool> Order(T x, const array<T, LOG>& basis) {
    T res = 0, aux = x;
    for (int k = LOG - 1; k >= 0; --k)  {
      if (basis[k] > T(0)) {
        res <<= 1;
        res |= ((x >> k) & T(1));
        aux = min(aux, aux ^ basis[k]);
      }
    }
    return { res, aux == T(0) }; // Returns false if cant gen
  }
};
