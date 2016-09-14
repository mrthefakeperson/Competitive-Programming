sq=input()
r=input()
c=input()
l=0
mapAll=[]
for _ in range(r):
    _i=raw_input()
    mapAll.append([])
    for e in _i:
        mapAll[_].append(e)
    mapAll[_].append("I")
mapAll.append([])
for e in xrange(c):
    mapAll[r].append("I")
#print mapAll
#globalCounter=0
def count1(x,y,L):
    if mapAll[y][x]==".":
        mapAll[y][x]="I"
        L.append(())
        count1(x+1,y,L)
        count1(x-1,y,L)
        count1(x,y+1,L)
        count1(x,y-1,L)
lst=[]
for e in xrange(r):
    for ch in xrange(c):
        if mapAll[e][ch]==".":
            globalCounter=[]
            count1(ch,e,globalCounter)
            #print globalCounter,len(globalCounter)
            lst.append(len(globalCounter))
lst.sort()
lst.reverse()
c=0
for e in lst:
    if sq-e<0:
        break
    sq-=e
    c+=1
iif="rooms,"
if c==1:
    iif="room,"
print c,iif,sq,"square metre(s) left over"
