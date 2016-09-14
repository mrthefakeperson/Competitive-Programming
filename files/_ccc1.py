import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)

cnt=[0]*26
st=i()
for e in st:
    cnt[ord(e)-ord("a")]+=1

st2=i()
for e in st2:
    if e<>"*":
        cnt[ord(e)-ord("a")]-=1

for e in xrange(26):
    if cnt[e]<0:
        print "N"
        break
else:
    print "A"
