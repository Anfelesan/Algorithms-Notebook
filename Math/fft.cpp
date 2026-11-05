// Based on
// https://github.com/ahoraSoyPeor/notebook_descomUNAL/blob/master/Math/Fast%20fourier%20transform.cpp
void FFT(vector<complex<double>>& a) {
  int n = int(a.size()), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<complex<double>> rt(2, 1);
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n); rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    for(int i = k; i < 2 * k; ++i) {
      rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
  }
  vector<int> rev(n);
  for (int i = 0; i < n; ++i) {
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  }
  for (int i = 0; i < n; ++i) {
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for (int k = 1; k < n; k *= 2) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; ++j) {
        // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
        auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
        complex<double> z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]); /// exclude-line
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
    }
  }
}
vector<ll> Polymult(const vector<ll>& a, const vector<ll>& b) {
  if (a.empty() || b.empty()) return {};
  vector<double> res(int(a.size()) + int(b.size()) - 1);
  int L = 32 - __builtin_clz(int(res.size())), n = 1 << L;
  vector<complex<double>> in(n), out(n);
  copy(a.begin(), a.end(), begin(in));
  for (int i = 0; i < int(b.size()); ++i) {
    in[i].imag(b[i]);
  }
  FFT(in);
  for (auto& x: in) x *= x;
  for (int i = 0; i < n; ++i) {
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  }
  FFT(out);
  vector<ll> resp(int(res.size()));
  for (int i = 0; i < int(res.size()); ++i) {
    resp[i] = round(imag(out[i]) / (4.0 * n));
  }
  return resp;
}
// Tested on: https://codeforces.com/contest/2231/submission/384108518
