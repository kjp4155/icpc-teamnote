const int N_ = 2e5;
const int inf = ~0u>>1;

struct node{
  inline void pushdown()
  {
    if( rev ){
      if( link[0] ) link[0]->rev ^= 1;
      if( link[1] ) link[1]->rev ^= 1;
      swap( link[0], link[1] );
      rev = 0;
    }
    if( add ){
      if( link[0] ) link[0]->add += add, link[0]->mn += add, link[0]->val += add;
      if( link[1] ) link[1]->add += add, link[1]->mn += add, link[1]->val += add;
      add = 0;
    }
  }

  inline void pushup()
  {
    cnt = (link[0]? link[0]->cnt:0) + (link[1]? link[1]->cnt:0) + 1;
    mn = min( val, min(link[0]?link[0]->mn:inf, link[1]?link[1]->mn:inf));
  }

  int cnt, add, mn, val; //cnt: number of nodes
  bool rev;
  node *link[2], *par;
};

struct splaytree{
  node N[ N_ ];
  node* root;
  int sz;
  
  node* operator[](int idx){ return N + idx; }

  void clear(int s){
    sz = 0;
    for(int i=0;i<=s+2;i++){
      N[i].link[0] = N[i].link[1] = N[i].par = 0, N[i].cnt = 1;
      N[i].rev = false;
    }
// dummy nodes can remove many null-pointer exceptions
    root = N+s+1; root->cnt = 2;
    N[s+2].par = N+s+1; N[s+1].link[1] = N+s+2;
  }

  inline int dir(node *x){ return x->par->link[0] != x; }
  inline int cnt(node* p){ return p? p->cnt: 0; }

  void rotate(node *n) // To 
  {
    n->par->pushdown(); n->pushdown();
    node *p = n->par;
    int d = dir(n);
    p->link[d] = n->link[!d];   if( n->link[!d] ) n->link[!d]->par = p;
    n->par = p->par;  if( p->par ) p->par->link[ dir(p) ] = n;
    n->link[!d] = p;  p->par = n;
    p->pushup(); n->pushup();
  }

  void splay(node *x, node *f){
    if( x == f ) return;
    while(x->par != f){
      x->par->pushdown();
      if( x->par->par == f );
      else if(dir(x) == dir(x->par)) rotate(x->par);
      else rotate(x);
      rotate(x);
    }
    x->pushdown();
    if( f == NULL ) root = x;
  }
// 1-index if dummy node exists
  node* kth_splay(int k,node* f)
  {
    node *x = root;
    x->pushdown();
    while( cnt( x->link[0] ) != k ){
      if( cnt( x->link[0] ) < k ){
        if( !x->link[1] ) return x;
        k -= cnt(x->link[0]) + 1, x = x->link[1];
      }
      else x = x->link[0];
      x->pushdown();
    }
    splay( x, f );
    return x;
  }
// 1-index if dummy nodes exist
// recommend: don’t copy & paste code below.
// be careful if dummy nodes don’t exist (ex. null-pointer exception)
  void insert(int wi, node *n) 
  {
    if( !root ){
      root = n;
      return;
    }
    kth_splay(wi-1, 0);
    kth_splay(wi, root);
    root->link[1]->link[0] = n; n->par = root->link[1];
    root->link[1]->pushup(); root->pushup();
  }
  
  void Delete(int x){
    kth_splay(x-1,0);
    kth_splay(x+1,root);
    root->link[1]->link[0] = NULL;
    root->link[1]->pushup(); root->pushup();
  }

  void Reverse(int x,int y){
    if( x > y ) return;
    kth_splay(x-1,0);
    kth_splay(y+1,root);
    root->link[1]->link[0]->rev ^= 1;
  }
  
  void revolve(int x,int y,int T){ // rotate x~y T times 
    if( x >= y ) return;
    int l = (y-x+1);
    T = (T%l+l) % l;
    Reverse(x,y-T);
    Reverse(y-T+1,y);
    Reverse(x,y);
  }

  int node_address(int wi)
  {
    node *p = N+wi;
    splay(p, 0);
    return cnt( p->link[0] );
  }

  int min(int x,int y){
    kth_splay(x-1,0);
    kth_splay(y+1,root);
    return root->link[0]->link[1]->mn;
  }
} pre, post;
