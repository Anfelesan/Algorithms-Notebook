struct HopcroftKarp {
  int n, m;
  vector<vector<int>> g;
  vector<int> dist, l_match, r_match;
  HopcroftKarp(int _n, int _m) : n(_n), m(_m), g(_n), dist(_n), l_match(_n, -1), r_match(_m, -1) {}
  void AddEdge(int u, int v) {
    g[u].push_back(v);
  }
  bool Bfs() {
    queue<int> que;
    for (int u = 0; u < n; ++u) {
      if (l_match[u] == -1) {
        dist[u] = 0;
        que.push(u);
      } else {
        dist[u] = INT_MAX;
      }
    }
    bool ok = false;
    for (; !que.empty(); que.pop()) {
      int u = que.front();
      for (int v: g[u]) {
        if (r_match[v] == -1) {
          ok = true;
        } else if (dist[r_match[v]] == INT_MAX) {
          dist[r_match[v]] = dist[u] + 1;
          que.push(r_match[v]);
        }
      }
    }
    return ok;
  }
  bool Dfs(int u) {
    for (int v: g[u]) {
      if (r_match[v] == -1 || (dist[u] + 1 == dist[r_match[v]] && Dfs(r_match[v]))) {
        l_match[u] = v;
        r_match[v] = u;
        return true;
      }
    }
    dist[u] = INT_MAX;
    return false;
  }
  vector<pair<int, int>> GetMatching() {
    while (Bfs()) {
      for (int u = 0; u < n; ++u) {
        if (l_match[u] == -1) Dfs(u);
      }
    }
    vector<pair<int,int>> matching;
    for (int u = 0; u < n; ++u) {
      if (l_match[u] > -1) {
        matching.emplace_back(u, l_match[u]);
      }
    }
    return matching;
  }
};

// Tested on: https://codeforces.com/contest/1721/submission/336469358
