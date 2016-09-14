def moves(x,y,pList):
    newList=[]
    for v in [-2,-1,1,2]:
        p1=(x+v,y+abs(v)-3)
        p2=(x+v,y-abs(v)+3)
        if p1 not in pList and p1[0]<=8 and p1[0]>0 and p1[1]<=8 and p1[1]>0:
            newList.append(p1)
            #print p1
        if p2 not in pList and p2[0]<=8 and p2[0]>0 and p2[1]<=8 and p2[1]>0:
            newList.append(p2)
            #print p2
    return newList
def update(L):
    upd=[]
    for e in L:
        upd+=moves(e[0],e[1],L)
    return upd
#def findInList(l1,l2):
#    for e in l1:
#        if e in l2:
#            return True
#    return False
points1=raw_input().split()
points2=raw_input().split()

L1,m=moves(int(points1[0]),int(points1[1]),[]),0
#L2=moves(int(points2[0]),int(points2[1]),[])
#m=2
#if points1!=points2:
m=1
#while not findInList(L1,L2):
while (int(points2[0]),int(points2[1])) not in L1:
    L1=update(L1)
    #L2=update(L2)
    #m+=2
    m+=1
    #print L1
if points1==points2:
    m=0
print m
