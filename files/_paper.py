import sys
i=lambda:sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n,r=ii()
adj=[
        [(lambda a,b:a+b) for e in xrange(5)],
        [(lambda a,b:2*r) for e in xrange(5)],
        [(lambda a,b:r) for e in xrange(5)],
        [(lambda a,b:a+r) for e in xrange(5)],
        [(lambda a,b:b+r) for e in xrange(5)]
    ]
adj[1][1]=lambda a,b:max(0,2*r)
adj[1][3]=lambda a,b:max(r,2*r)
adj[1][4]=lambda a,b:max(r,2*r)
adj[2][2]=lambda a,b:max(0,r)
adj[3][1]=lambda a,b:max(a,a+r)
adj[3][3]=lambda a,b:max(a,a+r)
adj[4][1]=lambda a,b:max(b,b+r)
adj[4][4]=lambda a,b:max(b,b+r)

ll1,ll2=ii(),ii()
state=[-99999999]*5
state[0]=0
for a,b in zip(ll1,ll2):
    nstate=[-99999999]*5
    for e in xrange(5):
        for ee in xrange(5):
            nstate[e]=max(nstate[e],state[ee]+adj[e][ee](a,b))
    state=nstate[:]
    #print state
print max(state)
