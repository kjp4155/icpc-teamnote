from sys import stdin
input = stdin.readline

def ccw(p1, p2, p3):
    # positive -> ccw; negative -> cw; 0 -> collinear
    return (p2[0]-p1[0])*(p3[1]-p1[1]) - (p2[1]-p1[1])*(p3[0]-p1[0])

def ULHull(p):
    U = []; L = []; p.sort()
    for q in p:
        while len(U)>1 and ccw(U[-2], U[-1], q) <= 0: U.pop()
        while len(L)>1 and ccw(L[-2], L[-1], q) >= 0: L.pop()
        U.append(q); L.append(q)
    return U, L

n = int(input())
p = [tuple(map(int,input().split())) for i in range(n)]
print(p)
U, L = ULHull(p)
print(U,L)
print(len(U)+len(L)-2)