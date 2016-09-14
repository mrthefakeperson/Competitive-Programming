lst=[False]*1000001
def filterAwesome():
    for e in xrange(2,1001):
        k=e**2
        while k<=1000000:
            lst[k]=False
            k+=e**2
            #print k
def filterSuper():
    e=1
    while e<1000000:
        e+=1
        #print lst[e]
        if lst[e]:
            #print e
            sumD=0
            for ch in str(e):
                sumD+=int(ch)
            if sumD%2<>0:
                lst[e]=False
def filterSpecial(num):
    lst[num]=True
    #print lst[num]
    N=num*10
    if N<1000000:
        for e in range(int(str(num)[-1])+1,10):
            filterSpecial(N+e)
filterSpecial(0)
filterAwesome()
filterSuper()
lst[1]=False
for e in xrange(5):
    _=raw_input().split(" ")
    _1,_2=int(_[0]),int(_[1])
    s=0
    for e in xrange(_1,_2+1):
        if lst[e]: s+=1
    print s
