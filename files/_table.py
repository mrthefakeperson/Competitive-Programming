import sys
def i(): return sys.stdin.readline().strip().split(" ")
_=i()
size,n=int(_[0]),int(_[1])
c=0
for ee in xrange(int(n**0.5)):
    e=ee+1
    if n%e==0:
        if e<=size and n/e<=size:
            if n/e<>e: c+=2
            else:c+=1
print c
