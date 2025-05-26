struct DSU {
  vector<int> par;
  vector<int> rank;
  int comps;
  DSU(int n) {
    par = vector<int>(n);
    rank = vector<int>(n, 1);
    iota(par.begin(), par.end(), 0);
    comps = n;
  }
  int Find(int v) {
    if (par[v] == v) return v;
    return par[v] = Find(par[v]);
  }
  bool Unite(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) return false;
    if (rank[b] < rank[a]) swap(a, b);
    if (rank[a] == rank[b]) ++rank[b];
    par[a] = b;
    --comps;
    return true;
  }
  bool Same(int a, int b) {
    return Find(a) == Find(b);
  }
  int CountComps() {
    return comps;
  }
};