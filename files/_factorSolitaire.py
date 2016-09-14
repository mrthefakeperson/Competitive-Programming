_,points=input(),0
while _<>1:
    for e in xrange(2,_+1):
        if _%e==0:
            N=_*(e-1)/e
            points+=N/(_-N)
            _=N
            break
print points
#is this seriously the solution xD
