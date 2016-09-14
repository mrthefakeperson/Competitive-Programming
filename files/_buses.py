import sys
_=sys.stdin.readline()[:-1].split(" ")
k=int(_[0])
time,required=int(_[1]),int(_[2])
buses=[]
breaks=0
for e in xrange(k):
    buses.append(int(sys.stdin.readline()[:-1]))
for e in xrange(len(buses)-2,-1,-1):
    while buses[e+1]-buses[e]>required:
        buses[e]+=time
        breaks+=1
#print buses
print breaks
