/*
  NOTE: Version 0 is a segment tree with all nodes containing default information
*/
// 0-indexed Persistent Segment Tree with a new version for each modification
const int inf = 1e9;
template<typename Info>
struct PersistentSegmentTree {
  struct Node {
    Node* lef = nullptr;
    Node* rig = nullptr;
    Info info = Info();
  };
  int len = 1;
  vector<Node*> versions;
  PersistentSegmentTree(int n) {
    while (len < n) len <<= 1;
    versions.push_back(new Node());
    Build(0, len - 1, versions[0]);
  }
  void Build(int l, int r, Node* node) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    node -> lef = new Node();
    node -> rig = new Node();
    Build(l, mid, node -> lef);
    Build(mid + 1, r, node -> rig);
  }
  Info Get(int ql, int qr, int version) {
    return Get(ql, qr, 0, len - 1, versions[version]);
  }
  Info Get(int ql, int qr, int l, int r, Node* node) {
    if (r < ql || qr < l) return Info();
    if (ql <= l && r <= qr) return node -> info;
    int mid = (l + r) >> 1;
    return Get(ql, qr, l, mid, node -> lef) + Get(ql, qr, mid + 1, r, node -> rig);
  }

  // Modify() creates a new version based on version (from)
  void Modify(int idx, Info v, int from) {
    versions.push_back(new Node());
    Update(0, len - 1, idx, v, versions[from], versions.back());
  }
  void Update(int l, int r, int idx, Info v, Node* base_node, Node* new_node) {
    if (l == r) {
      new_node -> info = v;
      return;
    }
    int mid = (l + r) >> 1;
    if (idx <= mid) {
      new_node -> lef = new Node();
      new_node -> rig = base_node -> rig;
      Update(l, mid, idx, v, base_node -> lef, new_node -> lef);
    } else {
      new_node -> rig = new Node();
      new_node -> lef = base_node -> lef;
      Update(mid + 1, r, idx, v, base_node -> rig, new_node -> rig);
    }
    new_node -> info = (new_node -> lef -> info) + (new_node -> rig -> info);
  }
  int GetVersionsCount() {
    return versions.size();
  }
};
struct Info {
  ...
};
Info operator + (const Info& l, const Info& r) {
  Info res = Info();
  ...
  return res;
}

// Tested on: https://codeforces.com/contest/1000/submission/355441679
