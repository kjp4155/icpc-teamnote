import sys

N = int(sys.stdin.readline())
arr = [int(x) for x in sys.stdin.readline().split()]

xlist = list(set(arr))
xlist.sort()

xmp = dict()

t = 1
for x in xlist:
	xmp[x] = t
	t = t + 1
	
print(xmp)
