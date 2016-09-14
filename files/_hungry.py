import sys

def eat(high,what):
    q,q2=abs(what-prev),abs(waterTemp-what)
    #print q,q2,what,prev,high
    if high:
        return max(q,q2)
    else:
        return min(q,q2)

_=sys.stdin.readline().strip().split(" ")
food,waterTemp=int(_[0]),int(_[1])
crackers=[int(sys.stdin.readline().strip()) for e in xrange(food)]
crackers.sort()
lowest,highest,prev=0,0,waterTemp
if abs(crackers[0]-waterTemp)>abs(crackers[-1]-waterTemp):crackers.reverse()
#for e in crackers:
    #print eat(False,e),e,prev
    #lowest+=eat(False,e)
    #prev=e
mm,mnn=max(crackers),min(crackers)
if mm>waterTemp and mnn>waterTemp:
    lowest=mm-waterTemp
elif mm<waterTemp and mnn<waterTemp:
    lowest=waterTemp-mnn
else:
    lowest=mm-mnn
prev=waterTemp
#print crackers
#if abs(crackers[0]-waterTemp)<abs(crackers[-1]-waterTemp):crackers.reverse()
for e in xrange(len(crackers)/2):
    highest+=eat(True,crackers[e])
    prev=crackers[e]
    highest+=eat(True,crackers[-e-1])
    prev=crackers[-e-1]
if food%2==1:highest+=eat(True,crackers[len(crackers)/2])
highest2,prev=0,waterTemp
crackers.reverse()
for e in xrange(len(crackers)/2):
    highest2+=eat(True,crackers[e])
    prev=crackers[e]
    highest2+=eat(True,crackers[-e-1])
    prev=crackers[-e-1]
if food%2==1:highest2+=eat(True,crackers[len(crackers)/2])
print lowest,max(highest,highest2)
