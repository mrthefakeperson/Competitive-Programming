import sys
def i(): return sys.stdin.readline().strip()

n=int(i())
arr=[0]+map(int,i().split())
acc=0
for e in xrange(1,n+1):
    acc+=abs(arr[e]-arr[e-1])
print acc