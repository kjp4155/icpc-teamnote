namespace Matching{
//matching [1...n] <-> [1...m]
const int MX = 40040, MY = 40040;
vector <int> E[MX];
int xy[MX], yx[MY];
int n, m;

void addE(int x, int y) { E[x].pb(y); }
void setnm(int sn, int sm) { n = sn; m = sm; }

int tdis[MX], que[MX], *dis = tdis + 1;
int bfs() {
  int *fr = que, *re = que;
  for(int i=1;i<=n;i++) {
    if(xy[i] == -1) *fr++ = i, dis[i] = 0;
    else dis[i] = -1;
  }
  dis[-1] = -1;
  while(fr != re) {
    int t = *re++;
    if(t == -1) return 1;
    for(int e : E[t]) {
      if(dis[yx[e]] == -1) dis[yx[e]] = dis[t] + 1, *fr++ = yx[e];
    }
  }
  return 0;
}

int dfs(int x) {
  for(int e : E[x]) {
    if(yx[e] == -1 || (dis[yx[e]] == dis[x] + 1 && dfs(yx[e]))) {
      xy[x] = e;
      yx[e] = x;
      return 1;
    }
  }
  dis[x] = -1;
  return 0;
}

int Do() {
  memset(xy, -1, sizeof xy);
  memset(yx, -1, sizeof yx);

  int ans = 0;
  while(bfs()) {
    for(int i=1;i<=n;i++) if(xy[i] == -1 && dfs(i)) ++ans;
  }
  return ans;
}
}


void solve(){
  int n, m;
  scanf("%d%d", &n, &m);
  Matching::setnm(n, m);
  for(int i=1;i<=n;i++) {
    int x; scanf("%d", &x);
    while(x--) {
      int y; scanf("%d", &y);
      Matching::addE(i, y);
    }
  }
  printf("%d\n", Matching::Do());
}
