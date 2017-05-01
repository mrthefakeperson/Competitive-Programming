import sys
sys.setrecursionlimit(99999999)
i = lambda: sys.stdin.readline().strip()
ii = lambda: map(int, i().split())

n = int(i())
adj = map(lambda e: e-1, ii())
z = ii()
visited = [False] * n
def src(x):
    e = x
    while not visited[e]:
        visited[e] = True
        e = adj[e]
acc = 0
for e in xrange(n):
    if not visited[e]:
        acc += 1
        src(e)
if acc == 1:
    acc = 0
if sum(z) % 2 == 0:
    acc += 1
print acc