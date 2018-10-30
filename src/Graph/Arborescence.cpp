namespace Arborescence{
  const int MX = 510, INF = 1e9;
  int e[MX][MX], lst[MX][MX];
  vector<int> v[MX], rev[MX], order;
  int was[MX], vst[MX], ans[MX], p[MX];
  vector<pii> G[MX];

  int find(int x){ return p[x] == x? x : p[x] = find(p[x]); }
  void set_graph(int ee[MX][MX]){ memcpy(e, ee, sizeof e); }

  void go(int x) {
    if(vst[x]) return;
    vst[x] = 1;
    for (int to : v[x]) go(to);
    order.pb(x);
  }

  void col(int x, int o) {
    if (was[x]) return;
    was[x] = o;
    for (int to : rev[x]) col(to, o);
  }

  int run(int n, int root) {
    int ret = 0, done = 0;
    for(int i = 1; i <= n; i++) p[i] = i;
    memset(lst, 0, sizeof lst);
    for(int tt = 1;;tt++) {
      memset(was, 0, sizeof was);
      memset(vst, 0, sizeof vst);
      for (int i = 1; i <= n; i++) {
        v[i].clear();
        rev[i].clear();
      }
      order.clear();

      int mn[MX] = {};
      for(int i = 1; i <= n; i++) mn[i] = INF;
      for (int i = 1; i <= n; i++) if (find(i) != find(root))
        for (int j = 1; j <= n; j++) if(find(i) != find(j))
          mn[find(i)] = min(mn[find(i)], e[j][i]);
      for (int i = 1; i <= n; i++) if (find(i) != find(root)) {
        if(find(i) == i) ret += mn[i];
        for (int j = 1; j <= n; j++) if(find(i) != find(j)) e[j][i] -= mn[find(i)];
      }
      for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++){
        int a = find(i), b = find(j);
        if (a != b && e[i][j] == 0) {
          lst[i][j] = tt;
          v[a].pb(b);
          rev[b].pb(a);
        }
      }
      if (done) break;
      for (int i = 1; i <= n; i++) if (!vst[i]) go(i);
      reverse(order.begin(), order.end());
      for(int u : order) if (!was[u]) col(u, u);
      done = 1;
      for(int i = 1; i <= n; i++) if(was[i] != i) done = 0, p[i] = was[i];
    }
    priority_queue<t3, vector<t3>, greater<t3>> Q;

    memset(ans, -1, sizeof ans);
    ans[root] = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
      if(e[i][j] == 0) G[i].emplace_back(lst[i][j], j);
    for(pii c : G[root]) Q.emplace(c.first, root, c.second);
    while(Q.size()){
      int a, b; tie(ignore, a, b) = Q.top(); Q.pop();
      if(ans[b] != -1) continue;
      ans[b] = a;
      for(pii c : G[b]) Q.emplace(c.first, b, c.second);
    }
    return ret;
  }
};
;
