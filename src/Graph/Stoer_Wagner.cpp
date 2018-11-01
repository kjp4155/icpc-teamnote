namespace stoer_wagner{
    const int MX = 505;
    int G[MX][MX], vst[MX], n;
    
    void init(int nn){ n = nn; memset(G, 0, sizeof G); }
    void add_edge(int a, int b, int d){ if(a != b) G[a][b] = G[b][a] = d; }
    
    pii minimum_cut_phase(int st, int &res){
        int dist[MX] = {}, vis[MX];
        int cur = 1e9, s = st, e = -1;
        memcpy(vis, vst, sizeof vst);
        dist[st] = 1e9;
        while(1){
            int mx = 0;
            for(int i=1;i<=n;i++) if(!vis[i] && (!mx || dist[mx] < dist[i])) mx = i;
            if(mx == 0) break;
            cur = dist[mx]; e = s; s = mx; vis[mx] = 1;
            for(int i = 1; i <= n; i++) dist[i] += G[mx][i];
        }
        res = min(res, cur);
        return pii(s, e);
    }
    int run(){
        if(n <= 1) return 0;
        memset(vst, 0, sizeof vst);
        int res = 1e9, t = 1, u;
        for(int i = 0; i < n-1; i++){
            tie(t, u) = minimum_cut_phase(t, res);
            vst[u] = 1;
            for(int i = 1; i <= n; i++){
                if(vst[i] || t == i) continue;
                G[t][i] += G[u][i]; G[i][t] += G[u][i];
            }
        }
        return res;
    }
};
