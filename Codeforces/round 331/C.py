import sys
def i(): return sys.stdin.readline().strip()


avail=[0]*200005
used=[0]*200005
n=int(i())
points=[[] for e in xrange(200005)]
for e in xrange(n):
    _=i().split()
    x,y=int(_[0]),int(_[1])
    points[y-x+100000].append((x,y))
    avail[y-x+100000]+=1
for e in points:
    e.sort()

ans=[]
thing=map(int,i().split(" "))
using=[[] for e in xrange(200005)]
places=[False]*200005
places[100000]=True     #+100000
canDo=True
for e in xrange(len(thing)):
    req=thing[e]+100000
    if not places[req] or avail[req]==0:
        print "NO"
        canDo=False
        break
    else:
        ans.append(points[req][used[req]])
        used[req]+=1
        avail[req]-=1
        places[req]=False
        places[req+1]=True
        if req-1>=0: places[req-1]=True
if canDo:
    print "YES"
    for e in ans: #print e[0],e[1]
        sys.stdout.write(str(e[0])+" "+str(e[1])+"\n")