import sys
i=lambda:sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

n=int(i())
picture=[[int(e) for e in i()] for ee in xrange(n)]
painted=[picture[e][:] for e in xrange(n)]
def black(a):
    top, bottom, left, right=a
    acc=0
    for e in xrange(top,bottom+1):
        for ee in xrange(left,right+1):
            acc+=picture[e][ee]
    return acc
def fill(a,v):
    top, bottom, left, right=a
    for e in xrange(top,bottom+1):
        for ee in xrange(left,right+1):
            painted[e][ee]=v
def answer(a):
    top, bottom, left, right=a
    if top==bottom: # and left==right:
        return 0
    else:
        mid1,mid2=(top+bottom)/2,(left+right)/2
        a,b,c,d=(top,mid1,left,mid2),(top,mid1,mid2+1,right),(mid1+1,bottom,left,mid2),(mid1+1,bottom,mid2+1,right)
        quadrants=[a,b,c,d]
        bl=map(black,quadrants)
        c=(mid1-top+1)*(mid1-top+1)
#        wh=map(lambda e:(mid1-top+1)*(mid1-top+1)-e,bl)
        an=map(answer,quadrants)
        anSum=sum(an)
        #print bl,wh,an,anSum
        accMin=99999999,()
        for e in xrange(4):
            for ee in xrange(4):
                if e<>ee:
                    ans=bl[e]+ c-bl[ee] +anSum-an[e]-an[ee]
                    if ans<accMin[0]:
                        accMin=ans,(e,ee)
        rr,(b,w)=accMin
        fill(quadrants[b],0)
        fill(quadrants[w],1)
        return rr
print answer((0,n-1,0,n-1))
for e in painted:
    for ee in e:
        sys.stdout.write(str(ee))
    sys.stdout.write("\n")