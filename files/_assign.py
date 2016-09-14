import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)

n=int(i())
lost=0
worked=0
for e in xrange(n):
    _=map(int,i().split(" "))
    a,b=_[0],_[1]
    worked+=b
    qq=worked
    worked=min(worked,a)
    lost+=qq-worked
print lost
#raw_input()
