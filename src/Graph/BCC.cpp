int N,M;
int timer = 0;
vector<int> E[300500];
int vis[300500], low[300500];

// dfs1 is to fill vis(discover time) and low array
int dfs1(int x, int pa){
    vis[x] = ++timer;
    low[x] = vis[x];    
    for(auto e : E[x])if(e!=pa){
        if( vis[e] ){
            low[x] = min(low[x], vis[e]);
        }
        else{
            dfs1(e,x);
            low[x] = min(low[x], low[e]);
        }
    }
    return low[x] ;
}

int color = 0;
vector<int> colors[300500], E2[300500];
int vis2[300500];

// dfs2 is to color every nodes
// Store node's colors into colors array
// Store new edges into E2
void dfs2(int x, int pa, int c){
    colors[x].pb(c);
    vis2[x] = 1;
    for(auto e : E[x])if(!vis2[e]){
        // x-e is an articulation edge
        if( low[e] > vis[x] ){
            ++color;
            colors[x].pb(color);
            E2[c].pb(color); E2[color].pb(c);
            dfs2(e,x,color);
        }
        // x-e is not an articulation edge
        else dfs2(e,x,c);
        
    }
}

int main(){
    geti(N,M);
    repp(i,M){
        int a, b; geti(a,b);
        E[a].pb(b); E[b].pb(a);
    }
    // fill vis & low 
    dfs1(1,-1);
    // find out articulation edge and color of nodes
    color = 1;
    dfs2(1,-1,color);
}
