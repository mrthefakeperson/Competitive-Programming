import sys
def i(): return sys.stdin.readline().strip()
n=int(i())
arr=map(int,i().split(" "))
left,right=[0]*n,[0]*n
leftPlaces,rightPlaces=[0]*n,[0]*n
target=sum(arr)/3
left[0]=arr[0]
right[n-1]=arr[n-1]
for e in xrange(n-1):
    left[e+1]=left[e]+arr[e+1]
    right[n-e-2]=right[n-e-1]+arr[n-e-2]
    
if left[0]==target:
    leftPlaces[0]=1
for e in xrange(n-1):
    leftPlaces[e+1]=leftPlaces[e]#+left[e+1]
    if left[e+1]==target:
        leftPlaces[e+1]+=1
if right[n-1]==target:
    rightPlaces[n-1]=1
for e in xrange(n-1,0,-1):
    rightPlaces[e-1]=rightPlaces[e]
    if right[e-1]==target:
        rightPlaces[e-1]+=1
#print leftPlaces
#print rightPlaces
mm=0
if sum(arr)%3<>0:
    print 0
else:
    for e in xrange(n-2):
        if e==0:
            if leftPlaces[0]<>0:
                nn=rightPlaces[e+2]
                mm+=nn
        elif leftPlaces[e]<>leftPlaces[e-1]:
            mm+=rightPlaces[e+2]
    print mm
#for e in xrange(n-1):
    
