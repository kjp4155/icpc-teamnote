G has a feasible (s,t)-flow iff G' has a saturating (s',t')-flow
in G' total capacity out of s' and into t' are both D (sum of demands)
saturating flow : flow with value exactly D.

1. Make new source, new sink (s', t')

2. for every v: 
c'(s'->v) = sum{ d(u->v) } (give demands into v)
c'(v->t') = sum{ d(v->w) } (take demands out of v)

3. for every u->v:
c'(u->v) = c(u->v) - d(u->v)  (difference of cap, demand)

4. make t->s cap:INF

maxflow mf;
lint lsum;
void clear(){
	lsum = 0;
	mf.clear();
}
void add_edge(int s, int e, int l, int r){
	lsum += l;
	mf.add_edge(s + 2, e + 2, r - l);
	mf.add_edge(0, e + 2, l);
	mf.add_edge(s + 2, 1, l);
}
bool solve(int s, int e){
	mf.add_edge(e+2, s+2, 1e9); // to reduce as maxflow with lower bounds, in circulation problem skip this line
	return lsum == mf.match(0, 1);
	// to get maximum LR flow, run maxflow from s+2 to e+2 again
}
