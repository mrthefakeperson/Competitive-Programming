import sys
def splitAmongMin(split,among,m):
    if (split,among,m) in sMap:
        i=sMap.get((split,among,m))
        #print len(sMap)
        return i
    if among==2:
        #print "count:",split/2-m+1
        l=split/2-m+1
        #print split,among,m
        sMap[(split,among,m)]=l
        return l
    else:
        k=0
        for e in range(m,split/among+1):
            k+=splitAmongMin(split-e,among-1,e)
            #print "|",e,"|",split,among,m
        sMap[(split,among,m)]=k
        return k
#print splitAmongMin(6,[0,0],1)
n=int(sys.stdin.readline()[:-1])
ppl=int(sys.stdin.readline()[:-1])
sMap={}
if ppl==1 or ppl==n: print 1
else: print splitAmongMin(n,ppl,1)
