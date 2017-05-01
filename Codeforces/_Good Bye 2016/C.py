import sys
i=lambda:sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n = int(i())
rating,div = [0], []
for e in xrange(n):
    a,b = ii()
    rating.append(rating[-1]+a)
    div.append(b)
end = rating[-1]
r = zip(rating[:-1],div)
r.sort()
for e in xrange(n-1):
    if r[e][1] == 1 and r[e+1][1] == 2:
        print "Impossible"
        break
else:
    if r[0][1] == 1:
        print "Infinity"
    else:
        pl = 0
        for e in xrange(n):
            if r[e][1] == 2:
                pl = e
        a = r[pl][0]+1
        print end-a+1900