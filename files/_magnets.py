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
metal=[]
white,black=[],[]
for e in xrange(n):
    _=i().split(" ")
    x,y=int(_[0]),int(_[1])
    clD=100000
    for e in magnets:
        clD=min(clD,abs(e[0]-x)+abs(e[1]-y))
    clD-=1
    if clD!=-1:
        if (x-clD+y)%2==0:
            white.append(((x-clD+y,y+1-(x-clD-1)),-1))
            white.append(((x+clD+1+y+1,y+1-(x+clD+1)),-1))
            white.append(((x+y-clD,y-clD-x),1))
            white.append(((x+y+clD+2,y+clD+2-x),1))
            black.append(((x-clD+y+1,y+1-(x-clD)),-1))
            black.append(((x+clD+y+1,y+1-(x+clD)),-1))
            black.append(((x+y-clD+1,y-clD+1-x),1))
            black.append(((x+y+clD+1,y+clD+1-x),1))
        else:
            black.append(((x-clD+y,y+1-(x-clD-1)),-1))
            black.append(((x+clD+1+y+1,y+1-(x+clD+1)),-1))
            black.append(((x+y-clD,y-clD-x),1))
            black.append(((x+y+clD+2,y+clD+2-x),1))
            white.append(((x-clD+y+1,y+1-(x-clD)),-1))
            white.append(((x+clD+y+1,y+1-(x+clD)),-1))
            white.append(((x+y-clD+1,y-clD+1-x),1))
            white.append(((x+y+clD+1,y+clD+1-x),1))

white.sort(sorter1)
white.sort(sorter2)
black.sort(sorter1)
black.sort(sorter2)
#print white, black

def stuff(ll):
    prevY=0
    accRow=[0]*4000
    globalMax=0
    for e in ll:
        a,b,c=e[0][0]/2,e[0][1],e[1]
        sw=0
        if b!=prevY:
            #sweep
            for ee in accRow:
                sw+=ee
                globalMax=max(globalMax,sw)
            prevY=b
        if a<0:accRow[0]+=c
        elif a>=4000:accRow[3999]+=c
        else:accRow[a]+=c
    sw=0
    for ee in accRow:
        sw+=ee
        globalMax=max(globalMax,sw)
    return globalMax
print max(stuff(white),stuff(black))

raw_input()
