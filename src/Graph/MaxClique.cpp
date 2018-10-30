ll G[40]; // 0-index
void get_clique(int R = 0, ll P = (1ll<<N)-1, ll X = 0){
  if((P|X) == 0){
    cur = max(cur, R);
    return;
  }
  int u = __builtin_ctzll(P|X);
  ll c = P&~G[u];
  while(c){
    int v = __builtin_ctzll(c);
    get_clique(R + 1, P&G[v], X&G[v]);
    P ^= 1ll << v;
    X |= 1ll << v;
    c ^= 1ll << v;
  }
}
