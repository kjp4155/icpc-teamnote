// LiChaoTree for dynamic CHT trick
// This example maintains CHT for finding MAXIMUM of corresponding x
// op=1 : add ax + b into CHT
// op=2 : find max value of position x
// https://cp-algorithms.com/geometry/convex_hull_trick.html
ll f(Pll line, ll x){
    return line.Fi*x + line.Se;
}

vector<ll> xlist;
struct LiChaoTree{
    int n; vector<Pll> d;
    void init(int x){
        n = 1; while (n < x) n *= 2;
        d.resize(n*2+10);
        for(auto& e : d){
            e = {0, -3*(1e18)};
        }
    }

    void insert(int node, int nL, int nR, Pll newline){
        if( nL == nR ){    
            if( f(d[node], xlist[nL]) < f(newline, xlist[nL]) ) d[node] = newline;
            return;
        }
        bool left = f(d[node], xlist[nL]) < f(newline, xlist[nL]);
        bool right = f(d[node], xlist[nR]) < f(newline, xlist[nR]);

        // take upper, lower line based on leftmost point of the segment
        Pll upper = d[node], lower = newline;
        if( left ) swap(upper, lower);

        // one line totally cover another line
        if( left == right ){
            d[node] = upper; return;
        }

        int m = (nL+nR)/2;
        // intersection in left half segment
        if( f(upper, xlist[m]) <= f(lower, xlist[m]) ){
            d[node] = lower;
            insert(node*2,nL,m, upper);
        }
        // intersection in right half segment
        else{
            d[node] = upper;
            insert(node*2+1,m+1,nR,lower);
        }
    }

    ll query(int node, int nL, int nR, int pos){
        if( nL == nR ) return f(d[node], xlist[pos]);
        
        int m = (nL+nR)/2;
        ll nval = -3*(1e18);
        if( pos <= m ) nval = query(node*2, nL, m, pos);
        else nval = query(node*2+1, m+1, nR, pos);

        return max(nval, f(d[node], xlist[pos]) );
    }

};

int main(){
    int Q; scanf("%d",&Q);
    vector<pair<int,Pll>> qlist;
    repp(q,Q){
        int op; scanf("%d",&op);
        if( op == 1 ){
            ll a,b; scanf("%lld%lld",&a,&b);
            qlist.push_back({1,{a,b}});
        }
        else{
            ll x; scanf("%lld",&x);
            xlist.push_back(x);
            qlist.push_back({2,{x,x}});
        }
    }

    xlist.push_back(-2*(1e12) - 10);
    sort(all(xlist));
    xlist.erase(unique(all(xlist)), xlist.end());
    LiChaoTree tree;
    tree.init( sz(xlist)+1 );

    // careful to put padding into xlist
    // so that it fits to tree size
    while( sz(xlist) < tree.n+5 )  xlist.push_back(2*(1e12));

    for(auto q : qlist){
        if( q.Fi == 1 ){
            tree.insert(1,1,tree.n,q.Se);
        }
        if( q.Fi == 2 ){
            int pos = lower_bound(all(xlist), q.Se.Fi) - xlist.begin();
            printf("%lld\n",tree.query(1,1,tree.n,pos));
        }
    }

}