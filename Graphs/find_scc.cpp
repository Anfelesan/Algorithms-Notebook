// 0-Indexed Graph
struct Graph {
  int n, curtag, timer;
  vector<vector<int>> graph;
  vector<bool> stacked, vis;
  vector<int> tag, tin;
  stack<int> stk;
  Graph(int _n) : n(_n), graph(_n) {}
  void AddEdge(int from, int to) {
    graph[from].push_back(to);
  }
  int Dfs(int node) {
    vis[node] = true;
    stacked[node] = true;
    tin[node] = ++timer;
    stk.push(node);
    int low = INT_MAX;
    for (int adj: graph[node]) {
      if (stacked[adj]) low = min(low, tin[adj]);
      if (!vis[adj]) low = min(low, Dfs(adj));
    }
    if (low == tin[node] || low == INT_MAX) {
      while (tag[node] == -1) {
        tag[stk.top()] = curtag;
        stacked[stk.top()] = false;
        stk.pop();
      }
      ++curtag;
      return INT_MAX;
    }
    return low;
  };
  void FindSCC() {
    stacked = vector<bool>(n, false);
    vis = vector<bool>(n, false);
    tag = vector<int>(n, -1);
    tin = vector<int>(n);
    while (!stk.empty()) stk.pop();
    timer = 0, curtag = 0;
    for (int node = 0; node < n; ++node) {
      if (!vis[node]) Dfs(node);
    }
  }
  int GetTag(int node) {
    return tag[node];
  }
  int CountComps() {
    return curtag;
  }
};
