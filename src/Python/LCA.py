import sys

sys.setrecursionlimit(150000)

N = int(sys.stdin.readline())
E = [[]for i in range(N+5)]
lev = [0 for i in range(N+5)]
pa = [ [-1 for i in range(N+5)] for j in range(18) ]

def dfs(x,p,l):
    pa[0][x] = p
    lev[x] = l
    for e in E[x]:
        if e == p: continue
        dfs(e,x,l+1)

def build_lca():
    for k in range(1,18):
        for n in range(1,N+1,1):
            if pa[k-1][n] == -1:
                pa[k][n] = -1
            else:
                pa[k][n] = pa[k-1][ pa[k-1][n] ]

def lca(a,b):
    if lev[a] < lev[b]:
        a,b = b,a

    diff = lev[a] - lev[b]
    for k in range(18):
        if ( diff & (1<<k) ) > 0:
            a = pa[k][a]
    
    if a == b :
        return a

    for k in range(17,-1,-1):
        if pa[k][a] != pa[k][b]:
            a = pa[k][a]
            b = pa[k][b]

    return pa[0][a]

for i in range(N-1):
    a,b = [int(x) for x in sys.stdin.readline().split()]
    E[a].append(b)
    E[b].append(a)

dfs(1,-1,1)
build_lca()

M = int(sys.stdin.readline())
for i in range(M):
    a,b =  [int(x) for x in sys.stdin.readline().split()]
    print(lca(a,b))
