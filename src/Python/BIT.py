import sys
import collections


N,M,K = [int(x) for x in sys.stdin.readline().split() ]
data = [0] * (N+20)

def update(p,x):
    original = query(p,p)
    diff = x - original
    while p <= N:
        data[p] = data[p] + diff
        p = p + (p&-p)

def query(l,r):
    res = 0
    l = l - 1
    while r > 0:
        res = res + data[r]
        r = r - (r&-r)
    while l > 0 :
        res = res - data[l]
        l = l - (l&-l)

    return res

for i in range(1,N+1,1):
    x = int(sys.stdin.readline())
    update(i,x)


for i in range(M+K):
    a,b,c = [int(x) for x in sys.stdin.readline().split() ]
    if a == 1:
        update(b,c)
    else:
        if b > c :
            swap(b,c)
        print(query(b,c))
