#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using Pos = pair<double, double>;
using vP = vector<Pos>;

ll n;
vP pts;
vl par;
vector<tuple<double, ll, ll>> edges{};

double Dist(const Pos& p, const Pos& q) {
  const auto& dx = p.first - q.first;
  const auto& dy = p.second - q.second;

  return std::sqrt(dx * dx + dy * dy);
}

ll GetRoot(ll x) {
  if (par[x] == x) return x;

  return par[x] = GetRoot(par[x]);
}

void Joint(ll x, ll y) {
  x = GetRoot(x);
  y = GetRoot(y);

  if (x == y) return;

  par[max(x, y)] = min(x, y);
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> n;
  pts = vP(n);
  for (auto&& [x, y] : pts) {
    cin >> x >> y;
  }

  par = vl(n);
  for (auto i = 0; i < n; ++i) {
    par[i] = i;
  }

  edges.reserve(n * n);
  for (auto i = 0; i < n; ++i) {
    for (auto j = i + 1; j < n; ++j) {
      edges.push_back({Dist(pts[i], pts[j]), i, j});
    }
  }
  sort(edges.begin(), edges.end());

  double ans = 0;
  for (const auto& [di, p, q] : edges) {
    const auto& rp = GetRoot(p);
    const auto& rq = GetRoot(q);

    if (rp == rq) continue;

    Joint(rp, rq);
    ans += di;
  }

  cout << fixed << setprecision(5) << ans;

  return 0;
}