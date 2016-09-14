n=input()
_=n
ppm=2147483648
pow2=[1]
for e in xrange(31):
    pow2.append(pow2[-1]*2)
rlimit=[]
pow2.reverse()
for e in pow2:
    if _-e<0:rlimit.append(False)
    else:
        rlimit.append(True)
        _-=e
saved=[[[] for e in xrange(32)],[[] for e in xrange(32)]]
visited=[[False]*32,[False]*32]
rlimit.reverse()
#rlimit=[False]+rlimit
#print rlimit
pee=[0]*33
def numbers(eligibleForLookup,rightPlace,previous):
    #if visited[previous][rightPlace]:
        #return saved[previous][rightPlace]
    #visited[previous][rightPlace]=True
    rr=[]
    if eligibleForLookup:
        if visited[previous][rightPlace]: return saved[previous][rightPlace]
        visited[previous][rightPlace]=True
        if rightPlace==0:
            #one way to make 0 ones, one way to make one ones
            if previous: rr=[(1,1)]
            else: rr=[(1,0)]
        else:
            if previous:        #last step True
                #rr=[]
                l1,l2=numbers(True,rightPlace-1,False),numbers(True,rightPlace-1,True)
                p1,p2,ll1,ll2=0,0,len(l1),len(l2)
                flag=True
                while p1<ll1 or p2<ll2:
                    a=(0,0)
                    if p1==ll1:
                        a=(l2[p2][0],l2[p2][1]+1); p2+=1
                    elif p2==ll2:
                        a=(l1[p1][0],l1[p1][1]+1); p1+=1
                    else:
                        if l1[p1][1]<l2[p2][1]:
                            a=(l1[p1][0],l1[p1][1]+1); p1+=1
                        else:
                            a=(l2[p2][0],l2[p2][1]+1); p2+=1
                    if flag:
                        rr.append(a)
                        flag=False
                    elif a[1]==rr[-1][1]:
                        rr[-1]=(a[0]+rr[-1][0],a[1])
                    else:
                        rr.append(a)
                #for e in rr:
                    #if e[1]<=(rightPlace+1)/2:qq+=e[0]
                #return rr
            else:
                #rr=[]
                l1,l2=numbers(True,rightPlace-1,False),numbers(True,rightPlace-1,True)
                p1,p2,ll1,ll2=0,0,len(l1),len(l2)
                flag=True
                while p1<ll1 or p2<ll2:
                    a=(0,0)
                    if p1==ll1:
                        a=l2[p2]; p2+=1
                    elif p2==ll2:
                        a=l1[p1]; p1+=1
                    else:
                        if l1[p1][1]<l2[p2][1]:
                            a=l1[p1]; p1+=1
                        else:
                            a=l2[p2]; p2+=1
                    if flag:
                        rr.append(a)
                        flag=False
                    elif a[1]==rr[-1][1]:
                        rr[-1]=(a[0]+rr[-1][0],a[1])
                    else:
                        rr.append(a)
                #return rr
        saved[previous][rightPlace]=rr
                
    else:
        if rightPlace==0:
            #if not(previous and not rlimit[0])
            if previous: rr=[(1,1)]
            else: rr=[(1,0)]
        else:
            #rr=[]
            if rlimit[rightPlace-1]:
                #print rightPlace
                if previous:
                    l1,l2=numbers(True,rightPlace-1,False),numbers(False,rightPlace-1,True)
                    p1,p2,ll1,ll2=0,0,len(l1),len(l2)
                    flag=True
                    while p1<ll1 or p2<ll2:
                        a=(0,0)
                        if p1==ll1:
                            a=(l2[p2][0],l2[p2][1]+1); p2+=1
                        elif p2==ll2:
                            a=(l1[p1][0],l1[p1][1]+1); p1+=1
                        else:
                            if l1[p1][1]<l2[p2][1]:
                                a=(l1[p1][0],l1[p1][1]+1); p1+=1
                            else:
                                a=(l2[p2][0],l2[p2][1]+1); p2+=1
                        if flag:
                            rr.append(a)
                            flag=False
                        elif a[1]==rr[-1][1]:
                            rr[-1]=(a[0]+rr[-1][0],a[1])
                        else:
                            rr.append(a)
                else:
                    l1,l2=numbers(True,rightPlace-1,False),numbers(False,rightPlace-1,True)
                    p1,p2,ll1,ll2=0,0,len(l1),len(l2)
                    flag=True
                    while p1<ll1 or p2<ll2:
                        a=(0,0)
                        if p1==ll1:
                            a=l2[p2]; p2+=1
                        elif p2==ll2:
                            a=l1[p1]; p1+=1
                        else:
                            if l1[p1][1]<l2[p2][1]:
                                a=l1[p1]; p1+=1
                            else:
                                a=l2[p2]; p2+=1
                        if flag:
                            rr.append(a)
                            flag=False
                        elif a[1]==rr[-1][1]:
                            rr[-1]=(a[0]+rr[-1][0],a[1])
                        else:
                            rr.append(a)
                    
                
            else:
                if previous: rr=map(lambda x:(x[0],x[1]+1),numbers(False,rightPlace-1,False))
                else: rr=numbers(False,rightPlace-1,False)
    if previous and pee[rightPlace]==0:
        for e in rr:
            if e[1]<=(rightPlace+1)/2:
                #print e,rightPlace+1
                pee[rightPlace]+=e[0]
    #if not eligibleForLookup:print rr,previous,rightPlace
    return rr
numbers(False,31,False)
#print saved
#print pee
print "There are %i round numbers less than or equal to %i." %(sum(pee),n)
#print sum(pee)

