import sys
from random import randint
def access(number):
    k[number]+=1
    return k[number]==1

gates=int(sys.stdin.readline().strip())
#gates=100000
k=[0]*(gates+1)
_=int(sys.stdin.readline().strip())
#_=100000
_2=_
stop=False
for e in xrange(_):
    __=int(sys.stdin.readline().strip())
    #__=randint(1,gates)
    #print"entered:",__
    cop=access(__)
    while not cop:
        __+=1-k[__]
        cop=access(__)
        if __<=0:
            stop=True
            break
    #print k,__
    if stop:
        _2=e
        break

print _2
