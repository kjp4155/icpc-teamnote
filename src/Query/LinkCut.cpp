#define _CRT_SECURE_NO_WARNINGS
#include<algorithm>
#include<stdio.h>

using namespace std;
const int N_ = 2e5;

struct node{
  void pushup(){
    cnt = (link[0]? link[0]->cnt:0) + (link[1]? link[1]->cnt:0) + 1;
    mx = max( max( link[0]? link[0]->mx:0, link[1]? link[1]->mx:0 ), val);
  }

  int cnt, val, mx; //cnt: number of nodes
  node *link[2], *par, *path_parent;
};

struct linkcuttree{
  node N[ N_ ];

  void clear(int s){
    for(int i=0;i<=s;i++)
      N[i].link[0] = N[i].link[1] = N[i].par = N[i].path_parent = 0, N[i].cnt = 1;
  }
  
  inline int dir(node *x){ return x->par->link[0] != x; }
  inline int cnt(node *x){ return x?x->cnt:0; }
  inline int mx(node *x){ return x?x->mx:0; }

  void rotate(node *n) // To 
  {
    if( !n->par ) return;
    node *p = n->par;
    int d = dir(n);
    n->path_parent = p->path_parent; p->path_parent = NULL;
    p->link[d] = n->link[!d];   if( n->link[!d] ) n->link[!d]->par = p;
    n->par = p->par;  if( p->par ) p->par->link[ dir(p) ] = n;
    n->link[!d] = p;  p->par = n;
    p->pushup(); n->pushup();
  }

  void splay(node *x){
    while( x->par ){
      if( !x->par->par );
      else if(dir(x) == dir(x->par)) rotate(x->par);
      else rotate(x);
      rotate(x);
    }
  }

  void access(node* x)
  {
    splay(x);
    if( x->link[1] ) x->link[1]->path_parent = x, x->link[1]->par = NULL;
    x->link[1] = NULL; x->pushup();
    while( x->path_parent ){
      node *pp = x->path_parent, *r;
      splay(pp);
      r = pp->link[1];
      if( r ) r->par = NULL, r->path_parent = pp;
      pp->link[1] = x; pp->pushup(); x->par = pp;
      x->path_parent = NULL;
      splay(x);
    }
  }

  void cut(int u)
  {
    access(N+u);
    if( N[u].link[0] ) N[u].link[0]->par = NULL;
    N[u].link[0] = NULL; N[u].pushup();
  }

  void link(int u, int v) // u must be root. 
  {
    if( u == v ) return;
    access(N+u);
    access(N+v);
    //assert(!N[u].link[0]);
    N[u].link[0] = N+v; N[v].par = N+u; N[u].pushup();
  }

// recommend: don’t copy & paste code below.
  int read(int u)
  {
    access( N+u );
    return N[u].cnt;
}

  int root(int u)
  {
    access( N+u );
    node* ans = N+u;
    while( ans->link[0] ) ans = ans->link[0];
    splay(ans);
    return ans - N;
  }

  int mx(int u)
  {
    access( N+u );
    return N[u].max;
  }

  bool chk()
  {
    for(int i=0;i<N_;i++){
      if( N[i].cnt == 0 ) return true;
      if( N[i].cnt != cnt(N[i].link[0]) + cnt(N[i].link[1]) + 1) return false;
      if( N[i].mx != max( max( mx(N[i].link[0]), mx(N[i].link[1]) ), N[i].val) ) return false;
      if( N[i].par && N+i != N[i].par->link[dir(N+i)] ) return false;
      if( N[i].link[0] && N+i != N[i].link[0]->par) return false;
      if( N[i].link[1] && N+i != N[i].link[1]->par) return false;
    }
    return true;
  }
}LCT;
