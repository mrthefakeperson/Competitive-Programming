import sys
def i(): return sys.stdin.readline().strip()

def sorter1(a,b):
    if a[0][0]>b[0][0]:return 1
    elif a[0][0]==b[0][0]:return 0
    else:return -1
def sorter2(a,b):
    if a[0][1]>b[0][1]:return 1
    elif a[0][1]==b[0][1]:return 0
    else:return -1

m=int(i())
magnets=[]
for e in xrange(m):
    _=i().split(" ")
    magnets.append((int(_[0]),int(_[1])))
n=int(i())
grid=[[0]*4001 for e in xrange(4000)]
white,black=[],[]
for e__ in xrange(n):
    _=i().split(" ")
    x,y=int(_[0]),int(_[1])
    clD=100000
    for e in magnets:
        clD=min(clD,abs(e[0]-x)+abs(e[1]-y))
    #clD-=1
    acc=0
    for e_ in xrange(x-clD+1,x+clD):
        if e_>=0 and e_<4000:
            grid[e_][max(0,y-acc)]+=1
            grid[e_][min(4000,y+acc+1)]-=1
        if e_<x:
            acc+=1
        else:
            acc-=1
mmm=0
for e in xrange(4000):
    sw=0
    for ee in xrange(4001):
        sw+=grid[e][ee]
        mmm=max(mmm,sw)
print mmm

raw_input()
