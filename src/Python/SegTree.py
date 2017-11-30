import sys
import collections

class segTree:
    def __init__(self, x):
        self.n = 1
        while self.n < x:
            self.n = self.n * 2
        self.data = [0 for i in range(self.n*2+10)]

    def query(self,l,r,node,nodeL,nodeR):
        if r < nodeL or l > nodeR:
            return 0
        if l <= nodeL and nodeR <= r:
            return self.data[node]
        val1 = self.query(l,r,node*2,nodeL,(nodeL+nodeR)//2)
        val2 = self.query(l,r,node*2+1,(nodeL+nodeR)//2+1,nodeR)
        return val1 + val2

    def update(self,p,x):
        p = p + self.n - 1
        self.data[p] = x
        p = p//2
        while p > 0:
            self.data[p] = self.data[p*2] + self.data[p*2+1]
            p = p // 2


N,M,K = [int(x) for x in sys.stdin.readline().split() ]
tree = segTree(N)
for i in range(1,N+1,1):
    x = int(sys.stdin.readline())
    tree.update(i,x)

for i in range(M+K):
    a,b,c = [int(x) for x in sys.stdin.readline().split() ]
    if a == 1:
        tree.update(b,c)
    else:
        if b > c :
            swap(b,c)
        print(tree.query(b,c,1,1,tree.n))