import sys
def i():return int(sys.stdin.readline())

_m_=1000000007
_=i()
cool_dudes=[i() for e in xrange(_)]
#spent=[0]+[e+1 for e in xrange(_)]
def insert(toLeft,howMany):
    ways=[1]*(toLeft+1)
    for e in xrange(howMany-1):
        ss=0
        for ee in xrange(toLeft+1):
            ss+=ways[ee]
            ss%=_m_
            ways[ee]=ss
        #print ways
    _ss=0
    for e in ways:_ss=(_ss+e)%_m_
    return _ss
thing=0
acc=0
mm=1
for e in cool_dudes:
    #print mm
    if e<>1:mm=(mm*insert(thing,e-1))%_m_
    thing+=e
print mm%_m_
