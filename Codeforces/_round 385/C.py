import sys
sys.setrecursionlimit(99999999)
i = lambda: sys.stdin.readline().strip()
ii = lambda: map(int, i().split())

n, m, k = ii()
gov = map(lambda e: e-1, ii())
adj = [[] for e in xrange(n)]
edges = [tuple(map(lambda e: e-1, ii())) for _ in xrange(m)]
for a,b in edges:
    adj[a].append(b)
    adj[b].append(a)
visited = [-1] * n
def src(i, n):
    visited[n] = i
    acc = 1
    for e in adj[n]:
        if visited[e] == -1:
            acc += src(i, e)
    return acc
govV, govE = [0]*n, [0]*n
gMax, gSum = 0, 0
for e in gov:
    s = src(e, e)
    govV[e] = s
    gMax = max(gMax, s)
    gSum += s
untaken = 0
for a,b in edges:
    if visited[a] == -1 and visited[b] == -1:
        untaken += 1
    else:
        govE[visited[a]] += 1
acc = (n-gSum) * (n-gSum-1) / 2 - untaken
for e in gov:
    acc += govV[e]*(govV[e]-1)/2 - govE[e]
acc += gMax * (n-gSum)
print acc
#print govV, govE, visited