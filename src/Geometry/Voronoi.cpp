typedef pair<double, double> pdd;
 
int get_det(pii a, pii b, pii c, pii d) {
    // 1 : out, -1 : in, 0 : boundary
    b.Fi -= a.Fi; c.Fi -= a.Fi; d.Fi -= a.Fi;
    b.Se -= a.Se; c.Se -= a.Se; d.Se -= a.Se;
    __int128 vb = (ll)b.Fi * b.Fi + (ll)b.Se * b.Se;
    __int128 vc = (ll)c.Fi * c.Fi + (ll)c.Se * c.Se;
    __int128 vd = (ll)d.Fi * d.Fi + (ll)d.Se * d.Se;
    __int128 res = b.Fi * (c.Se * vd - d.Se * vc) - c.Fi * (b.Se * vd - d.Se * vb) + d.Fi * (b.Se * vc - c.Se * vb);
    if(res > 0) return 1;
    else if(res == 0) return 0;
    else return -1;
}
 
const int MAXN = 2020;
const int INF = 10010;
int C[MAXN+5][MAXN+5];
void get_delaunay(vector <pii> pts, vector <t3> &L) {
    vector <pii> P;
    P.pb(pii(-INF*INF*4, -INF*INF*4));
    P.pb(pii(INF*INF*4, -INF*INF*4));
    P.pb(pii(0, INF*INF));
    rep(i, szz(pts)) P.pb(pts[i]);
    int N = szz(P);
    rep(i, N) rep(j, N) C[i][j] = 0;
    vector <t3> Tri;
    Tri.pb(t3(0, 1, 2));
    auto get_c = [&](int x, int y) { return C[x][y] + C[y][x]; };
    for(int i=3;i<N;i++) {
        int m = szz(Tri);
        vector <int> bad_t;
        rep(j, m) {
            int a, b, c;
            tie(a, b, c) = Tri[j];
            if(get_det(P[a], P[b], P[c], P[i]) == -1) {
                bad_t.pb(j);
                C[a][b]++; C[b][c]++; C[c][a]++;
            }
        }
        for(int e : bad_t) {
            int a, b, c;
            tie(a, b, c) = Tri[e];
            if(get_c(a, b) == 1) Tri.pb(t3(a, b, i));
            if(get_c(b, c) == 1) Tri.pb(t3(b, c, i));
            if(get_c(c, a) == 1) Tri.pb(t3(c, a, i));
        }
 
        for(int e : bad_t) {
            int a, b, c;
            tie(a, b, c) = Tri[e];
            C[a][b] = C[b][c] = C[c][a] = 0;
        }
 
        reverse(all(bad_t));
        for(int e : bad_t) {
            swap(Tri[e], Tri.back());
            Tri.pop_back();
        }
    }
    for(t3 e : Tri) {
        int a, b, c;
        tie(a, b, c) = e;
        if(min({a, b, c}) >= 3) L.pb(t3(a-3, b-3, c-3));
    }
}