import sys
def i(): return int(sys.stdin.readline().strip())
sys.setrecursionlimit(99999999)

w,i,l,d,c,a,t,s,vowels,consonants,wild=i(),i(),i(),i(),i(),i(),i(),i(),i(),i(),i()

vv=[i,a]
cc=[w,l,d,c,t,s]
def optimize(ll,amtt):
    ll.sort()
    amt=amtt
    for e in xrange(len(ll)-1):
        wanted=(ll[e+1]-ll[e])*(e+1)
        if amt<wanted:
            __=amt%(e+1)
            for ee in xrange(e+1):
                ll[ee]+=amt/(e+1)
            for ee in xrange(__):
                ll[ee]+=1
            amt=0
        else:
            for ee in xrange(e+1):
                ll[ee]+=wanted/(e+1)
            amt-=wanted
    if amt<>0:
        __=amt%len(ll)
        for ee in xrange(len(ll)):
            ll[ee]+=amt/len(ll)
        for ee in xrange(__):
            ll[ee]+=1
optimize(vv,vowels)
optimize(cc,consonants)
aa=vv+cc
optimize(aa,wild)
#print aa,vv,cc
print min(aa)

#raw_input()
