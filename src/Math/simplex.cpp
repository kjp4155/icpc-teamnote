/*
LP Duality
tableu 를 대각선으로 뒤집고 음수 부호를 붙인 답 =  -( 원 문제의 답 )
ex) n = 2, m = 3, a = [[0.5, 2, 1], [1, 2, 4]], b = [24, 60], c = [6, 14, 13]
<=> n = 3, m = 2, a = [[-0.5, -1], [-2, -2], [-1, -4]], b = [-6, -14, -13], c = [-24, -60]

n := number of variables
m := number of constraints
a[1~m][1~n] := constraints
b[1~m] := constraints value (b[i] can be negative)
c[1~n] := maximum coefficient
v := results
sol[i] := 등호조건, i  번째    변수의 값
ex) Maximize p = 6x + 14y + 13z
    Constraints: 0.5x + 2y + z ≤ 24
                 x + 2y + 4z ≤ 60
    n = 2, m = 3, a = [[0.5, 2, 1], [1, 2, 4]], b = [24, 60], c = [6, 14, 13]
*/

namespace simplex {
  using T = long double;
  const int N = 410, M = 30010;
  const T eps = 1e-7;
  int n, m;
  int Left[M], Down[N];
  T a[M][N], b[M], c[N], v, sol[N];

  bool eq(T a, T b) { return fabs(a - b) < eps;  }
  bool ls(T a, T b) { return a < b && !eq(a, b); }

  void init(int p, int q) {
    n = p; m = q; v = 0;
    for(int i = 1; i <= m; i++){
      for(int j = 1; j <= n; j++) a[i][j]=0;
    }
    for(int i = 1; i <= m; i++) b[i]=0;
    for(int i = 1; i <= n; i++) c[i]=sol[i]=0;
  }

  void pivot(int x,int y) {
    swap(Left[x], Down[y]);
    T k = a[x][y]; a[x][y] = 1;
    vector<int> nz;
    for(int i = 1; i <= n; i++){
      a[x][i] /= k;
      if(!eq(a[x][i], 0)) nz.push_back(i);
    }
    b[x] /= k;

    for(int i = 1; i <= m; i++){
      if(i == x || eq(a[i][y], 0)) continue;
      k = a[i][y]; a[i][y] = 0;
      b[i] -= k*b[x];
      for(int j : nz) a[i][j] -= k*a[x][j];
    }
    if(eq(c[y], 0)) return;
    k = c[y]; c[y] = 0;
    v += k*b[x];
    for(int i : nz) c[i] -= k*a[x][i];
  }

  // 0: found solution, 1: no feasible solution, 2: unbounded
  int solve() {
    for(int i = 1; i <= n; i++) Down[i] = i;
    for(int i = 1; i <= m; i++) Left[i] = n+i;
    while(1) { // Eliminating negative b[i]
      int x = 0, y = 0;
      for(int i = 1; i <= m; i++) if (ls(b[i], 0) && (x == 0 || b[i] < b[x])) x = i;
      if(x == 0) break;
      for(int i = 1; i <= n; i++) if (ls(a[x][i], 0) && (y == 0 || a[x][i] < a[x][y])) y = i;
      if(y == 0) return 1;
      pivot(x, y);
    }
    while(1) {
      int x = 0, y = 0;
      for(int i = 1; i <= n; i++)
        if (ls(0, c[i]) && (!y || c[i] > c[y])) y = i;
      if(y == 0) break;
      for(int i = 1; i <= m; i++)
        if (ls(0, a[i][y]) && (!x || b[i]/a[i][y] < b[x]/a[x][y])) x = i;
      if(x == 0) return 2;
      pivot(x, y);
    }
    for(int i = 1; i <= m; i++) if(Left[i] <= n) sol[Left[i]] = b[i];
    return 0;
  }
}
