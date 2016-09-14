import sys
_=int(sys.stdin.readline().strip())
def case(tokens,start):
    below,above=[],[]
    for e in tokens:
        if int(e)>start:above.append(int(e))
        elif int(e)<start:below.append(int(e))
    belowHighest,aboveLowest=start,start
    c1,c2=True,True
    #print above,below,start
    while len(above)>0:
        if above[0]==aboveLowest+1:
            aboveLowest+=1
            above=above[1:]
        elif above[-1]==aboveLowest+1:
            aboveLowest+=1
            above=above[:-1]
        else:
            c1=False
            break
        #print above,aboveLowest,c1
    while len(below)>0:
        if below[0]==belowHighest-1:
            belowHighest-=1
            below=below[1:]
        elif below[-1]==belowHighest-1:
            belowHighest-=1
            below=below[:-1]
        else:
            c2=False
            break
        #print below,belowHighest,c2
    return c1 and c2
for e_ in xrange(_):
    sys.stdin.readline()
    tokens=sys.stdin.readline().strip().split(" ")
    rr=case(tokens,int(tokens[0])) or case(tokens,int(tokens[-1]))
    if rr:print "Case #"+str(e_+1)+": yes"
    else:print "Case #"+str(e_+1)+": no"
