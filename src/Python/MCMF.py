import sys
import collections

E = []; pv = []; pe = []; dist = []; inq = [];
INF = 99999999999999

class Edge:
    def __init__(self,to,inv,cap,flow,cost):
        self.to = to
        self.inv = inv
        self.cap = cap
        self.flow = flow
        self.cost = cost
    def res(self):
        return self.cap - self.flow

def make_edge(from1,to,cap,cost):
    forward = Edge(to,len(E[to]),cap,0,cost);
    backward = Edge(from1,len(E[from1]),0,0,-cost)
    E[from1].append(forward)
    E[to].append(backward)

def init(x):
    global E,inv,pv,pe,dist,inq
    E = [[] for i in range(x+10)]
    pv = [0 for i in range(x+10)]
    pe = [0 for i in range(x+10)]
    dist = [0 for i in range(x+10)]
    inq = [0 for i in range(x+10)]

def solve(source,sink):
    global E,inv,pv,pe,dist,inq
    ans = 0
    totalflow = 0
    totalcost = 0
    while True:
        dist = [INF] * len(dist)
        inq = [0] * len(inq)
        
        q = collections.deque()
        q.append(source)
        inq[source] = 1
        dist[source] = 0

        # SPFA
        while len(q) >= 1:
            cur = q.popleft()
            inq[cur] = 0
            for i in range(len(E[cur])):
                e = E[cur][i]
                if e.res() > 0 and dist[e.to] > dist[cur] + e.cost:
                    dist[e.to] = dist[cur] + e.cost
                    pv[e.to] = cur
                    pe[e.to] = i
                    if inq[e.to] == 0:
                        inq[e.to] = 1
                        q.append(e.to)

        if dist[sink] == INF:
            break

        # Add this limit when we don't require maxflow
        #if dist[sink] > 0: break

        mnflow = INF
        v = sink
        while v != source:
            mnflow = min(mnflow, E[pv[v]][pe[v]].res())
            v = pv[v]

        v = sink
        while v != source:
            tmp = E[pv[v]][pe[v]].inv
            E[pv[v]][pe[v]].flow += mnflow
            E[v][tmp].flow -= mnflow
            v = pv[v]

        totalflow += mnflow
        totalcost += dist[sink] * mnflow

    return(totalflow,totalcost)


N,M = [int(x) for x in sys.stdin.readline().split()]

init(N+M+10)

arr =  [int(x) for x in sys.stdin.readline().split()]
for i in range(1,N+1,1):
    make_edge(M+i,N+M+1,arr[i-1],0)

arr =  [int(x) for x in sys.stdin.readline().split()]
for i in range(1,M+1,1):
    make_edge(0,i,arr[i-1],0)

for i in range(1,M+1,1):
    arr = [int(x) for x in sys.stdin.readline().split()]
    for j in range(len(arr)):
        make_edge(i,M+j+1,INF,arr[j])


res = solve(0,N+M+1)
print(res[1])