import sys
sys.setrecursionlimit(99999999)
ii = lambda: map(int, sys.stdin.readline().split())

n,_ = ii()
ll = ii()
visited = {}
def src(x):
    if x not in visited:
        win = False
        for e in filter(lambda ee: x%ee==0, ll):
            if not src(x/e):
                win = True
                break
            #win = win or not src(x/e)
        visited[x] = win
    return visited[x]
if True in map(lambda e: e%2==0 and n%e==0, ll):
    print "First"
else:
    print ("First" if src(n) else "Second")