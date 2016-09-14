import sys
def mergeAdd(ll,first):
    rr=ll[:first]+[ll[first]+ll[first+1]]
    for e in xrange(first+2,len(ll)):
        rr.append(ll[e])
    return rr
def mergeSub(ll,first):
    rr=ll[:first]+[ll[first]-ll[first+1]]
    for e in xrange(first+2,len(ll)):
        rr.append(ll[e])
    return rr
def mergeMtp(ll,first):
    rr=ll[:first]+[ll[first]*ll[first+1]]
    for e in xrange(first+2,len(ll)):
        rr.append(ll[e])
    return rr
def mergeDvd(ll,first):
    #if ll[first]==13 and ll[first+1]==5:print ll
    #print ll[first],ll[first+1],"=",ll[first]/ll[first+1]
    if ll[first+1]<>0:
        if ll[first]%ll[first+1]==0:
            rr=ll[:first]+[ll[first]/ll[first+1]]
            for e in xrange(first+2,len(ll)):
                rr.append(ll[e])
            return rr
        else:return []
    else:
        return []
def stuff(ll,test):
    #print ll
    if len(ll)==0:return 0
    elif len(ll)<>1:
        rr=[]
        for e in xrange(len(ll)-1):
            rr.append(stuff(mergeAdd(ll,e),test+str(ll[e])+"+"+str(ll[e+1])+" "))
            rr.append(stuff(mergeSub(ll,e),test+str(ll[e])+"-"+str(ll[e+1])+" "))
            rr.append(stuff(mergeMtp(ll,e),test+str(ll[e])+"*"+str(ll[e+1])+" "))
            rr.append(stuff(mergeDvd(ll,e),test+str(ll[e])+"/"+str(ll[e+1])+" "))
        return max(rr)
    else:
        if ll[0]<=24:
            #if ll[0]==24:print test
            return ll[0]
        else:return 0
def permutate(ll,cmb):
    ck=True
    for e in ll:
        if e<>None:ck=False
    if ck:return cmb
    else:
        cc=[]
        for e in xrange(len(ll)):
            k_=ll[:]
            if k_[e]<>None:
                k_[e]=None
                cc+= permutate(k_,cmb+[ll[e]])
        return cc

def wrap():
    kk=[int(sys.stdin.readline().strip()),int(sys.stdin.readline().strip()),\
           int(sys.stdin.readline().strip()),int(sys.stdin.readline().strip())]
    acc=0
    L,b=[],[]
    for e in permutate(kk,[]):
        b.append(e)
        if acc%4==3:
            L.append(b)
            b=[]
        acc+=1
    currMax=0
    for e in L:
        mm=stuff(e,"")
        if mm>currMax:currMax=mm
    print currMax
_=int(sys.stdin.readline().strip())
for e in xrange(_):
    wrap()
