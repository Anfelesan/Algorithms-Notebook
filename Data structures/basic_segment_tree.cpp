// 0-Indexed Segment Tree
template <typename Node>
struct SegmentTree {
  vector<Node> tree;
  int len = 1;
  SegmentTree(int n) {
    while (len < n) len <<= 1;
    tree.resize(len << 1, Node());
  }
  Node Get(int idx) {
    return tree[len + idx];
  }
  Node Get(int ql, int qr) {
    return Get(ql, qr, 0, len - 1, 1);
  }
  Node Get(int ql, int qr, int l, int r, int node) {
    if (r < ql || qr < l) return Node();
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) >> 1;
    return Get(ql, qr, l, mid, node << 1) + Get(ql, qr, mid + 1, r, (node << 1) + 1);
  }
  void Pull(int node) {
    if (node >= len) return;
    tree[node] = tree[node << 1] + tree[(node << 1) + 1];
  }
  void Modify(int idx, const Node &v) {
    tree[len + idx] = v;
    for (int node = (len + idx) >> 1; node > 0; node >>= 1) {
      Pull(node);
    }
  }
};
struct Node {
  ...
};
Node operator + (const Node& a, const Node& b) {
  Node res;
  ...
  return res;
}
