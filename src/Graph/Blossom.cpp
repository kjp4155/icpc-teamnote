namespace Blossom {
    // from http://codeforces.com/blog/entry/49402
    const int MAX_N = 550;
    const int MAX_M = 130000;
    struct struct_edge{int v;struct_edge* n;};
    typedef struct_edge* edge;
    struct_edge pool[MAX_M*2];
    edge top,adj[MAX_N];
    int V,E,match[MAX_N],qh,qt,q[MAX_N],father[MAX_N],base[MAX_N];
    bool inq[MAX_N],inb[MAX_N],ed[MAX_N][MAX_N];
    void add_edge(int u,int v)
    {
        top->v=v,top->n=adj[u],adj[u]=top++;
        top->v=u,top->n=adj[v],adj[v]=top++;
    }
    int LCA(int root,int u,int v)
    {
        static bool inp[MAX_N];
        rep(i, V) inp[i] = 0;
        while(1)
        {
            inp[u=base[u]]=true;
            if (u==root) break;
            u=father[match[u]];
        }
        while(1)
        {
            if (inp[v=base[v]]) return v;
            else v=father[match[v]];
        }
    }
    void mark_blossom(int lca,int u)
    {
        while (base[u]!=lca)
        {
            int v=match[u];
            inb[base[u]]=inb[base[v]]=true;
            u=father[v];
            if (base[u]!=lca) father[u]=v;
        }
    }
    void blossom_contraction(int s,int u,int v)
    {
        int lca=LCA(s,u,v);
        rep(i, V) inb[i] = 0;
        mark_blossom(lca,u);
        mark_blossom(lca,v);
        if (base[u]!=lca)
            father[u]=v;
        if (base[v]!=lca)
            father[v]=u;
        for (int u=0;u<V;u++)
            if (inb[base[u]])
            {
                base[u]=lca;
                if (!inq[u])
                    inq[q[++qt]=u]=true;
            }
    }
    int find_augmenting_path(int s)
    {
        rep(i, V) father[i] = -1, inq[i] = 0;
        for (int i=0;i<V;i++) base[i]=i;
        inq[q[qh=qt=0]=s]=true;
        while (qh<=qt)
        {
            int u=q[qh++];
            for (edge e=adj[u];e;e=e->n)
            {
                int v=e->v;
                if (base[u]!=base[v]&&match[u]!=v){
                    if ((v==s)||(match[v]!=-1 && father[match[v]]!=-1))
                        blossom_contraction(s,u,v);
                    else if (father[v]==-1)
                    {
                        father[v]=u;
                        if (match[v]==-1)
                            return v;
                        else if (!inq[match[v]])
                            inq[q[++qt]=match[v]]=true;
                    }
                }
            }
        }
        return -1;
    }
    int augment_path(int s,int t)
    {
        int u=t,v,w;
        while (u!=-1)
        {
            v=father[u];
            w=match[v];
            match[v]=u;
            match[u]=v;
            u=w;
        }
        return t!=-1;
    }
    int edmonds()
    {
        int matchc=0;
        rep(i, V) match[i] = -1;
        for (int u=0;u<V;u++)
            if (match[u]==-1)
                matchc+=augment_path(u,find_augmenting_path(u));
        return matchc;
    }
    void solve(int n, vector <pii> Ed, vector <pii> &Mat) { // 1-based
        Mat.clear();
        if(szz(Ed) == 0) return;
        int m = szz(Ed);
        rep(i, n) rep(j, n) ed[i][j] = false;
        top=pool;
        rep(i, m*2) pool[i].v = 0, pool[i].n = NULL;
        rep(i, n) adj[i] = NULL;
        rep(i, n) match[i] = q[i] = father[i] = base[i] = 0;
        rep(i, n) inq[i] = inb[i] = 0;
        qh = qt = 0;
        V = n, E = m;
        rep(i, m) {
            int x = Ed[i].Fi - 1;
            int y = Ed[i].Se - 1;
            add_edge(x, y);
            ed[x][y] = ed[y][x] = true;
        }
        edmonds();
        rep(i, V) if(i < match[i]) Mat.emplace_back(i + 1, match[i] + 1);
    }
}