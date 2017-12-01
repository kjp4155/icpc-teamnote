import sys
import collections

sys.setrecursionlimit(15000)
Pi = collections.namedtuple('Pi',['Fi','Se'])

def dfs(x):
    vis[x] = 1
    mx = 0
    mxx = x
    for e in E[x]:
        if vis[e.Fi] == 1: continue
        res = dfs(e.Fi)
        if res.Se + e.Se > mx:
            mx = res.Se + e.Se
            mxx = res.Fi
    return Pi(mxx,mx)

N = int(sys.stdin.readline())
E = [[] for i in range(N+10) ]
vis = [0 for i in range(N+10)]
for i in range(N-1):
    a,b,c = [ int(x) for x in sys.stdin.readline().split() ]
    E[a].append(Pi(b,c))
    E[b].append(Pi(a,c))

res = dfs(1)
vis = [0 for i in range (N+10) ]
res = dfs(res.Fi)
print(res.Se)
