def fac(n):
    if facs[n]<>0:
        return facs[n]
    else:
        m=fac(n-1)*n
        facs[n]=m
        return m
facs=[0 for k in xrange(101)]
facs[0],facs[1]=0,1
mm=input()
for e in xrange(mm):
    print fac(input())
