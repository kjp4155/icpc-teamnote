import sys
import collections

Point = collections.namedtuple('Point',['x','y'])
INF = 9999999999999999999
arr = []

def ykey(a):
    return (a.y,a.x)

def xkey(a):
    return (a.x,a.y)

def dist(a,b):
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)

def solve(l,r):
    n = (r-l+1)
    if n == 1:
        return INF

    mid = (l+r)//2
    d = min(solve(l,mid), solve(mid+1,r))

    ml = mid
    while ml >= l and (arr[ml].x-arr[mid].x)**2 < d:
        ml -= 1
    mr = mid
    while mr <= r and (arr[mr].x-arr[mid].x)**2 < d:
        mr += 1

    midlist = arr[ml+1:mr]
    midlist.sort(key=ykey)

    for i in range(len(midlist)):
        for j in range(1,7,1):
            if i+j >= len(midlist):
                break
            d = min(d, dist(midlist[i],midlist[i+j]))

    return d

N = int(sys.stdin.readline())
for i in range(N):
    x,y = [int(x) for x in sys.stdin.readline().split()]
    p = Point(x,y)
    arr.append(p)

arr.sort(key=xkey)

print(solve(0,N-1))