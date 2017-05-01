import sys
i=lambda:sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n = int(i())
place = 0
for e in xrange(n):
    a,b = i().split(" ")
    a = int(a)
    if b == "North":
        place -= a
    elif b == "South":
        place += a
    elif place == 0 or place == 20000:
        print "NO"
        break
    if place < 0 or place > 20000:
        print "NO"
        break
else:
    if place == 0:
        print "YES"
    else:
        print "NO"