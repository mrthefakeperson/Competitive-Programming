ppm=2147483648
def check(n):
    q=2147483648
    s=32
    digits=0
    _1=0
    while q>0:
        if n-q>=0:
            if s>digits:digits=s
            n-=q
            _1+=1
        q/=2
        s-=1
    #print n,_1,digits,s
    return _1<=digits/2
nn=input()
cc=0
for e in xrange(nn):
    if check(e+1):
        cc+=1
        #print e+1
print cc
