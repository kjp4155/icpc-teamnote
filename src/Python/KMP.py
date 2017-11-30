import sys

def preprocess(p):
    n = len(p)
    fail = [0] * n
    j = 0
    for i in range(1,n,1):
        while j > 0 and p[i] != p[j] :
            j = fail[j-1]
        if p[i] == p[j]:
            j = j + 1
            fail[i] = j
        else:
            fail[i] = 0

    return fail

def KMP(s,p):
    n = len(s)
    m = len(p)
    j = 0
    ans = []
    fail = preprocess(p)
    for i in range(n):
        while j > 0 and s[i] != p[j]:
            j = fail[j-1]
        if s[i] == p[j]:
            if j == m-1:
                ans.append(i-m+1)
                j = fail[j]
            else:
                j = j + 1

    return ans

s = str(sys.stdin.readline().strip('\n'))
p = str(sys.stdin.readline().strip('\n'))

ans = KMP(s,p)

print(len(ans))
for x in ans:
    print(x+1,end='')
    print(" ",end='')
