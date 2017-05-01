import sys
def i(): return sys.stdin.readline().strip()
def gcd(a,b):
    if a==0: return b
    elif b==0: return a
    elif a>b:
        return gcd(a%b,b)
    else:
        return gcd(a,b%a)
n=int(i())
numbers=map(int,i().split(" "))
numbers.sort()
numbers.reverse()
nums,last=[],-1
for e in numbers:
    if nums==[]:
        nums.append((e,1))
        last=e
    else:
        if e==last:
            q=nums.pop()
            nums.append((q[0],q[1]+1))
        else:
            nums.append((e,1))
            last=e
#print nums
#raw_input()
qq=len(nums)
def getI(e):
    jump=qq
    currentI=0
    while jump>1:
        jump/=2
        if nums[currentI+jump][0]>=e:
            currentI+=jump
    while nums[currentI][0]>e: currentI+=1
    while nums[currentI][0]<e: currentI-=1
    return currentI
        
rr=[]
for e in xrange(len(nums)):
    nn=nums[e][0]
    #print numbers
    while nums[e][1]>0:
        print nn,
        nums[e]=(nums[e][0],nums[e][1]-1)
        for ee in rr:
            thing=gcd(ee,nn)
            ii=getI(thing)
            nums[ii]=(nums[ii][0],nums[ii][1]-2)
        rr.append(nn)