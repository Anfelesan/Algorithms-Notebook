#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

ordered_set</*DataType*/> oset; // Declaration

// Methods
auto iterator_of_the_element_at_index_idx = oset.find_by_order(idx) // 0-indexed
int number_of_strictly_smaller_elements = oset.order_of_key(x); // Count of elements < x

// Implementation to manage multiple equal elements
template <class T>
struct ordered_multiset {
  ordered_set<pair<T, int>> os;
  map<T, int> mp; // Optimization: Replace the map with vector<int>(max_value + 1, 0) if all elements are integers in [0, max_value].

  void insert(T x) {
    os.insert(make_pair(x, ++mp[x]));
  }
  void erase(T x) {
    if (mp[x] == 0) return;
    os.erase(make_pair(x, mp[x]--));
  }
  int order_of_key(T x) {
    return os.order_of_key(make_pair(x, 0));
  }
  T find_by_order(int idx) {
     return (*os.find_by_order(idx)).first;
  }
  int count(T x) {
    return mp[x];
  }

  int size() { return (int)os.size(); }
  bool empty() { return os.empty(); }
  void clear() { os.clear(); }
};
