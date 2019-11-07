
/* This is MAX Lichao Tree*/
struct LiChaoTree{
    ll f(Line l, ll x){
        return l.first * x + l.second;
    }
    struct Node{
        int lnode, rnode;
        ll xl, xr;
        Line l;
    };
    vector<Node> nodes;
    void init(ll xmin, ll xmax){
        nodes.push_back({-1,-1,xmin,xmax,{0,-1e18}});
    }

    void insert(int n, Line newline){
        ll xl = nodes[n].xl, xr = nodes[n].xr;
        ll xm = (xl + xr) >> 1;
        
        Line llow = nodes[n].l, lhigh = newline;
        if( f(llow, xl) >= f(lhigh,xl) ) swap(llow, lhigh);

        if( f(llow, xr) <= f(lhigh, xr) ){
            nodes[n].l = lhigh;
            return;
        }

        else if( f(llow, xm) <= f(lhigh, xm) ){
            nodes[n].l = lhigh;
            if( nodes[n].rnode == -1 ){
                nodes[n].rnode = nodes.size();
                nodes.push_back({-1,-1,xm+1,xr,{0,-1e18}});
            }
            insert(nodes[n].rnode, llow);
        }

        else{
            nodes[n].l = llow;
            if( nodes[n].lnode == -1 ){
                nodes[n].lnode = nodes.size();
                nodes.push_back({-1,-1,xl,xm,{0,-1e18}});
            }
            insert(nodes[n].lnode, lhigh);
        }
    }
    ll get(int n, ll xq){
        if( n == -1 ) return -1e18;
        ll xl = nodes[n].xl, xr = nodes[n].xr;
        ll xm = (xl + xr) >> 1;

        if( xq <= xm ) return max(f(nodes[n].l, xq), get(nodes[n].lnode, xq));
        else return max(f(nodes[n].l, xq), get(nodes[n].rnode, xq));
    }
};

int main() {
    LiChaoTree tree;
    tree.init(-2e12, 2e12);

    int Q; scanf("%d",&Q);
    for(int q=0;q<Q;q++){
        ll op, a, b;
        scanf("%lld",&op);
        if( op == 1 ){
            scanf("%lld%lld",&a,&b);
            tree.insert(0, {a,b});
        }
        if( op == 2 ){
            scanf("%lld",&a);
            printf("%lld\n",tree.get(0, a));
        }
    }

}

// This is MIN Lichao tree //
struct LiChaoTree{
    ll f(Line l, ll x){
        return l.first * x + l.second;
    }
    struct Node{
        int lnode, rnode;
        ll xl, xr;
        Line l;
    };
    vector<Node> nodes;
    void init(ll xmin, ll xmax){
        nodes.push_back({-1,-1,xmin,xmax,{0,1e18}});
    }

    void insert(int n, Line newline){
        ll xl = nodes[n].xl, xr = nodes[n].xr;
        ll xm = (xl + xr) >> 1;
        
        Line llow = nodes[n].l, lhigh = newline;
        if( f(llow, xl) >= f(lhigh,xl) ) swap(llow, lhigh);

        if( f(llow, xr) <= f(lhigh, xr) ){
            nodes[n].l = llow;
            return;
        }

        else if( f(llow, xm) <= f(lhigh, xm) ){
            nodes[n].l = llow;
            if( nodes[n].rnode == -1 ){
                nodes[n].rnode = nodes.size();
                nodes.push_back({-1,-1,xm+1,xr,{0,1e18}});
            }
            insert(nodes[n].rnode, lhigh);
        }

        else{
            nodes[n].l = lhigh;
            if( nodes[n].lnode == -1 ){
                nodes[n].lnode = nodes.size();
                nodes.push_back({-1,-1,xl,xm,{0,1e18}});
            }
            insert(nodes[n].lnode, llow);
        }
    }
    ll get(int n, ll xq){
        if( n == -1 ) return 1e18;
        ll xl = nodes[n].xl, xr = nodes[n].xr;
        ll xm = (xl + xr) >> 1;

        if( xq <= xm ) return min(f(nodes[n].l, xq), get(nodes[n].lnode, xq));
        else return min(f(nodes[n].l, xq), get(nodes[n].rnode, xq));
    }
};

