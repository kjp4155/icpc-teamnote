import sys
import collections

class Edge:
    def __init__(self,to,inv,cap):
        self.to = to
        self.inv = inv
        self.cap = cap
        self.flow = 0
    def res(self):
        return self.cap - self.flow

n = 0
E = []
lev = []
work = []

def init(x):
    global E
    global lev
    global work
    n = x+5
    E = [ [] for i in range(n) ]
    lev = [0 for i in range(n) ]
    work = [0 for i in range(n) ]

def make_edge(from1,to,cap):
    forward = Edge(to,len(E[to]),cap)
    backward = Edge(from1,len(E[from1]),0)
    E[from1].append(forward)
    E[to].append(backward)

def bfs(source,sink):
    q = collections.deque()
    for i in range(len(lev)):
        lev[i] = -1
    lev[source] = 0
    q.append(source)
    while len(q) >= 1:
        cur = q.popleft()
        for e in E[cur]:
            if lev[e.to] == -1 and e.res() > 0:
                lev[e.to] = lev[cur] + 1
                q.append(e.to)
    return lev[sink] != -1

def dfs(cur,sink,flow):
    if cur == sink:
        return flow
    while work[cur] < len(E[cur]):
        i = work[cur]
        e = E[cur][i]
        if e.res() == 0 or lev[e.to] != lev[cur]+1:
            work[cur] = work[cur] + 1
            continue
        df = dfs(e.to,sink,min(flow, e.res() ) )
        if df > 0 :
            e.flow += df
            E[e.to][e.inv].flow -= df
            return df
        work[cur] = work[cur] + 1
    return 0

def solve(source, sink):
    ans = 0
    while bfs(source,sink) == True:
        for i in range(len(work)):
            work[i] = 0
        while True:
            flow = dfs(source,sink,99999999999)
            if flow == 0 :
                break
            ans = ans + flow
    return ans

N,M = [ int(x) for x in sys.stdin.readline().split() ]
init(N+M+5)

for i in range(1,N+1,1):
    make_edge(0,i,1)
for i in range(1,M+1,1):
    make_edge(N+i,N+M+1,1)

for i in range(1,N+1,1):
    arr = [ int(x) for x in sys.stdin.readline().split() ]
    for j in range(1,len(arr),1):
        make_edge(i,N+arr[j],1)

print(solve(0,N+M+1))
