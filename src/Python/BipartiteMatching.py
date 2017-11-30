import sys
import collections


N,M = [int(x) for x in sys.stdin.readline().split()]
vis = [0 for i in range(N+10) ]
xy = [0 for i in range(N+10) ]
yx = [0 for i in range(M+10) ] 
E = [ [] for i in range(N+2) ]

def dfs(x):
    vis[x] = True
    for e in E[x]:
        if yx[e] == 0 or ( vis[yx[e]] == False and dfs(yx[e]) == 1 ):
            yx[e] = x
            xy[x] = e
            return 1
    return 0 


for i in range(1,N+1,1):
    arr = [int(x) for x in sys.stdin.readline().split()]
    n = len(arr)
    for j in range(1,n,1):
        E[i].append(arr[j])

ans = 0
for i in range(1,N+1,1):
    for j in range(N+10):
        vis[j] = 0 
    ans = ans + dfs(i)

print(ans)