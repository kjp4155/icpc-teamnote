import sys
from bisect import *

N = int(sys.stdin.readline().strip())
arr = [int(x) for x in sys.stdin.readline().strip().split()]
M = int(sys.stdin.readline().strip())
arr2 = [int(x) for x in sys.stdin.readline().strip().split()]

arr.sort()

#print(arr)
for x in arr2:
    p = bisect_left(arr,x)
    #print(x,p,0,end='')
    if p < len(arr) and arr[p] == x:
        print(1)
    else:
        print(0)