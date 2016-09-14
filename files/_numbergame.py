import sys
n=int(sys.stdin.readline().strip())
numbers=[e for e in xrange(n+1)]
factor=[1]*(n+1)
ans=[0,[]]
for e in xrange(2,n+1):
    _=False
    kk=numbers[e]
    for ee in xrange(e,n+1):
        if numbers[ee]%kk==0 and kk<>1:
            numbers[ee]/=kk
            factor[ee]*=kk
            _=True
    if _:
        ans[0]+=1
        ans[1].append(e)
    #print numbers
print ans[0]
for e in ans[1]:
    print e,
