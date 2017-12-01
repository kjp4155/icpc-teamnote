import sys
from heapq import *
inf = 9989999999989



N,M = [int(x) for x in sys.stdin.readline().split()]
E = [[] for x in range(N+10)]

start = int(sys.stdin.readline())
for i in range(M):
    a,b,c = [int(x) for x in sys.stdin.readline().split()]
    forward = (b,c)
    E[a].append(forward)
    

dist = [inf]*20050
dist[start] = 0
pq = []
heappush(pq,(0,start))


while len(pq) > 0 :
    cur = heappop(pq)
    if cur[0] > dist[cur[1]]:
        continue

    for e in E[cur[1]]:
        if dist[e[0]] > cur[0] + e[1]:
            dist[e[0]] = cur[0] + e[1]
            heappush(pq,(dist[e[0]],e[0]))

for i in range(1,N+1,1):
    if dist[i] == inf:
        print("INF")
    else:
        print(dist[i])