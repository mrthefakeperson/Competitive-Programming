import sys
import math
def getOn(cars,on,new):
    k=132
    if new:k=251
    o=on
    for e in xrange(len(cars)):
        _=k-cars[e]
        cars[e]+=o
        if cars[e]>k:
            o=cars[e]-k
            cars[e]=k
        else:
            o=0
            break
    if o>0:
        for e in xrange(int(o/k)):
            o-=k
            cars.append(k)
    if o<>0:cars.append(o)
    return cars
_=int(sys.stdin.readline()[:-1])
passengers=0
old,new=[0],[0]
for e in xrange(_):
    k=sys.stdin.readline()[:-1].split(" ")
    on,off=float(k[0]),int(k[1])
    for e in xrange(len(old)):
        old[e]-=int(old[e]*off/100)
    for e in xrange(len(new)):
        new[e]-=int(new[e]*off/100)
    old=getOn(old,on,False)
    new=getOn(new,on,True)
    #print old,new
print int(len(old)-len(new))
