// Returns 0-indexed directed centroid tree as adjacency list, you may use up[]
// to get the parent of each node in the centroid tree
struct CentroidDecomposition {
  vector<vector<int>> tree, ctree;
  vector<bool> mark;
  vector<int> siz, up;
  int n, aux, gcent;

  CentroidDecomposition(int _n): n(_n) {
    tree.resize(n);
    ctree.resize(n);
    mark.resize(n, false);
    siz.resize(n);
    up.resize(n, -1);
  }
  void AddEdge(int u, int v) {
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  void DfsSiz(int node, int par) {
    siz[node] = 1;
    for (int child: tree[node]) {
      if (child == par || mark[child]) continue;
      DfsSiz(child, node);
      siz[node] += siz[child];
    }
  }
  int DfsCent(int node, int par) {
    for (int child: tree[node]) {
      if (child == par || mark[child]) continue;
      if (siz[child] * 2 > aux) return DfsCent(child, node);
    }
    return node;
  }
  int FindCentroid(int init) {
    DfsSiz(init, -1);
    aux = siz[init];
    return DfsCent(init, -1);
  }
  void Decompose() {
    queue<int> que;
    gcent = FindCentroid(0);
    for (que.push(gcent), mark[gcent] = true; !que.empty(); que.pop()) {
      int cent = que.front();
      for (int adj: tree[cent]) {
        if (!mark[adj]) {
          int child = FindCentroid(adj);
          ctree[cent].push_back(child);
          up[child] = cent;
          mark[child] = true;
          que.push(child);
        }
      }
    }
  }
  int GetGeneralCentroid() {
    return gcent;
  }
  vector<vector<int>> GetCentroidTree() {
    return ctree;
  }
};
