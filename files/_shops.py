#hungry for apples?
import sys
sys.setrecursionlimit(9999999)
def i():return sys.stdin.readline().strip().split(" ")
_=map(int,i())
n,space,money=_[0],_[1],_[2]
names_strings=[]
items=[]
for e in xrange(n):
    _=i()
    names_strings.append(_[0])
    items.append((int(_[1]),int(_[2]),int(_[3]),e))
visited=[[((0,0),-1) for e in xrange(money+1)]for ee in xrange(space+1)]
ideal=[[0]*(money+1) for e in xrange(space+1)]

#lookups=[0,0]

def HELP(x,y):
    if ideal[x][y]==0 and not(x==0 and y==0):
        
        #lookups[1]+=1
        
        mm=0
        xx,yy,used=0,0,-1
        for e in xrange(n):
            val,costX,costY,ind=items[e]
            #print val,costX,costY
            if x-costX>=0 and y-costY>=0:
                reted=HELP(x-costX,y-costY)
                if val+reted>mm:
                    mm=val+reted
                    xx,yy=x-costX,y-costY
                    used=e
                    #ll=nll[:]
                    #ll[ind]+=1
        ideal[x][y]=mm
        visited[x][y]=((xx,yy),used)
        #print x,y,ideal[x][y]
    #else:
        
        #lookups[0]+=1
        
    return ideal[x][y]
aa=HELP(space,money)
#print lookups[0],lookups[1]
print aa
ii=[0]*n
sch=(space,money)
while sch<>(0,0):
    #print sch
    indd=visited[sch[0]][sch[1]][1]
    if indd<> -1:
        ii[indd]+=1
    sch=visited[sch[0]][sch[1]][0]
for e in xrange(n):
    print names_strings[e],
    print ii[e]
#for e in xrange(len(bb)):
#    print names_strings[e],
#    print bb[e]
