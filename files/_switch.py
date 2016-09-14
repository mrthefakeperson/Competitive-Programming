import sys
__=int(sys.stdin.readline().strip())
one=False
status=[]
for e in xrange(__):
    status.append(bool(int(sys.stdin.readline().strip())))
def group(ll,pos):
    k,sig,i,i2=1,ll[pos],pos-1,pos+1
    while i>=0:
        if ll[i]<>sig:break
        i-=1
        k+=1
    while i2<len(ll):
        if ll[i2]<>sig:break
        i2+=1
        k+=1
    return k
def check(ll,pos):
    if pos==0:
        return ll[1]
    elif pos==len(ll)-1:
        return ll[-2]
    else:
        return (ll[pos-1] or ll[pos+1])
def hashList(ll):
    rr,kk="",ll[0]
    for e in xrange(len(ll)):
        if ll[e]<>kk:
            kk=not kk
            rr+=chr(e)
    return rr
visited,searchList,op={},[status],-1
visited[hashList(status)],stop=True,True
while stop:
    op+=1
    #print len(searchList)
    Nlist=[]
    for e in searchList:
        #print group(e,0)==__
        if group(e,0)==__:
            stop=False
            break
        for ee in xrange(len(e)):
            if not e[ee] and check(e,ee):
                nxt=e[:]
                nxt[ee]=True
                if group(nxt,ee)>=4:
                    nxt[ee]=False
                    i,i2=ee-1,ee+1
                    while i>=0:
                        if not nxt[i]:break
                        nxt[i]=False
                        i-=1
                    while i2<len(nxt):
                        if not nxt[i2]:break
                        nxt[i2]=False
                        i2+=1
                hh=hashList(nxt)
                if hh not in visited:
                    visited[hh]=True
                    Nlist.append(nxt)
    searchList=Nlist[:]
print op
