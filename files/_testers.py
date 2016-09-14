import sys
sve=[0]*100001
for e in xrange(1,100001):
    for x in xrange(e,100001,e):
        sve[x]+=1
#for e in sve:print e
#raw_input("done")
final=[[] for e in xrange(129)]
for e in xrange(1,len(sve)):
    #print sve[e]
    final[sve[e]].append(e)
#raw_input("done again")
#for e in final:print e
def binSFl(lst,findd):
    halfPoint=len(lst)/2
    breadth=halfPoint
    while not(lst[halfPoint]>=findd and lst[halfPoint-1]<findd):
        
        breadth/=2
        if breadth==0:breadth=1
        if lst[halfPoint-1]>=findd:
            halfPoint-=breadth
        elif lst[halfPoint]<findd:
            halfPoint+=breadth
        if halfPoint==0 or halfPoint==len(lst):break
        #print "hfP::",halfPoint
    return halfPoint
def binSCl(lst,findd):
    halfPoint=len(lst)/2
    breadth=halfPoint
    while not(lst[halfPoint]>findd and lst[halfPoint-1]<=findd):
        
        breadth/=2
        if breadth==0:breadth=1
        if lst[halfPoint-1]>findd:
            halfPoint-=breadth
        elif lst[halfPoint]<=findd:
            halfPoint+=breadth
        if halfPoint==0 or halfPoint==len(lst):break
        #print "hfP::",halfPoint
    return halfPoint
eeee=int(sys.stdin.readline().strip("\n"))
for kk in xrange(eeee):
    _=sys.stdin.readline().strip("\n").split(" ")
    w=int(_[0])
    uBound,lBound=int(_[2]),int(_[1])
    if w>128:print 0
    elif len(final[w])==0:print 0
    elif len(final[w])==1:
        if final[w][0]>=lBound and final[w][0]<=uBound:print 1
        else:print 0
    else:
        print binSCl(final[w],uBound)-binSFl(final[w],lBound)

