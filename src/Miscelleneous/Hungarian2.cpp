#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <numeric>
#include <functional>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <thread>
#include <tuple>
#include <limits>

using namespace std;


/*
Tests
http://www.spoj.com/problems/GREED/
https://www.acmicpc.net/problem/8992
SRM 506 mid

Time complexity O(n^3)

Usage
MinWeightBipartiteMatch matcher(n);
for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) matcher.weights[i][j] = SOMETHING;
cost_t total = matcher.solve();

See matcher.match(row -> col) and matcher.matched(col -> row) for actual match
*/

struct MinWeightBipartiteMatch
{
  typedef long long cost_t;

  cost_t max_cost() const { return numeric_limits<cost_t>::max(); }

  // input
  int n;
  vector<vector<cost_t>> weights;
  // output
  vector<int> match, matched;

  MinWeightBipartiteMatch(int n) :
    n(n), match(n), matched(n), weights(n, vector<cost_t>(n))
  {

  }

  void resize(int n) {
    this->n = n;
    match.resize(n);
    matched.resize(n);
    weights.resize(n);
    for (int i = 0; i < n; i++) {
      weights[i].resize(n);
    }
  }

  /* for solve() */
  vector<cost_t> slack;
  vector<cost_t> potential_row, potential_col;
  vector<int> reach_row, reach_col;
  int rcnt;
  vector<int> from;
  void found_match(int r, int c) {
    do {
      int old_match = match[r];
      match[r] = c;
      matched[c] = r;
      tie(r, c) = make_pair(from[r], old_match);
    } while (r >= 0 && c >= 0);
  }

  void augment(int row_to_match) {
    slack.resize(n);
    for (int c = 0; c < n; c++) {
      slack[c] = weights[row_to_match][c] - potential_row[row_to_match] - potential_col[c];
    }
    ++rcnt;
    vector<int> q; q.reserve(n);
    int h = 0;
    q.push_back(row_to_match);
    reach_row[row_to_match] = rcnt;
    from[row_to_match] = -1;
    for (;;) {
      while (h < q.size()) {
        int r = q[h++];
        for (int c = 0; c < n; c++) {
          cost_t gap = weights[r][c] - potential_row[r] - potential_col[c];
          slack[c] = min(slack[c], gap);
          if (gap != cost_t()) continue;
          int next = matched[c];
          if (next < 0) {
            found_match(r, c);
            return;
          }
          reach_col[c] = rcnt;
          if (reach_row[next] == rcnt) continue;
          q.push_back(next);
          reach_row[next] = rcnt;
          from[next] = r;
        }
      }
      cost_t delta = max_cost();
      for (int c = 0; c < n; c++) {
        if (reach_col[c] == rcnt) continue; // non-covered -> continue
        delta = min(delta, slack[c]);
      }
      for (int r = 0; r < n; r++) {
        if (reach_row[r] == rcnt) continue;
        potential_row[r] -= delta;
      }
      for (int c = 0; c < n; c++) {
        if (reach_col[c] == rcnt) continue;
        potential_col[c] += delta;
        slack[c] -= delta;
      }
      int lastsize = q.size();
      for (int c = 0; c < n; c++) {
        if (reach_col[c] == rcnt) continue;
        if (slack[c] != cost_t()) continue;
        int next = matched[c];
        if (next >= 0 && reach_row[next] == rcnt) continue;
        for (int qi = 0; qi < lastsize; qi++) {
          int r = q[qi];
          cost_t gap = weights[r][c] - potential_row[r] - potential_col[c];
          if (gap != cost_t()) continue;
          if (next < 0) {
            found_match(r, c);
            return;
          }
          reach_col[c] = rcnt;
          q.push_back(next);
          reach_row[next] = rcnt;
          from[next] = r;
          break;
        }
      }
    }
  }

  void initialize() {
    potential_row.assign(n, cost_t());
    potential_col.assign(n, cost_t());
    match.assign(n, -1);
    matched.assign(n, -1);
    reach_row.assign(n, 0);
    reach_col.assign(n, 0);
    from.resize(n);
    rcnt = 1;
    for (int i = 0; i < n; i++) {
      cost_t row_min_weight = *min_element(weights[i].begin(), weights[i].end());
      potential_row[i] = row_min_weight;
    }
    for (int i = 0; i < n; i++) {
      cost_t col_min_weight = weights[0][i] - potential_row[0];
      for (int j = 1; j < n; j++) col_min_weight = min(col_min_weight, weights[j][i] - potential_row[j]);
      potential_col[i] = col_min_weight;
    }
  }

  cost_t solve() {
    initialize();
    for (int row_to_match = 0; row_to_match < n; row_to_match++) {
      augment(row_to_match);
    }
    cost_t ans = cost_t();
    for (auto v : potential_row) ans += v;
    for (auto v : potential_col) ans += v;
    return ans;
  }
};

