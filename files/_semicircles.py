import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
MOD=1000000007

n=int(i())
k=int(i())
circles=[map(int,i().split(" ")) for e in xrange(k)]
#precompute
def precompute(ll,repeat):
    if repeat==0: return ll
    else:
        backward=ll[:]
        backward.reverse()
        ll.append(sum(map(lambda a:(a[0]*a[1])%MOD,zip(ll,backward)))%MOD)
        return precompute(ll,repeat-1)
fillGap=[]
for e in precompute([1,1],n/2+5):
    fillGap.append(e)
    fillGap.append(0)

#establish tree
circles.sort()
circles.reverse()
tree=[(e[0]-1,e[1]-1) for e in circles]+[(-1,n)]
#determine if the next element in the tree list is NOT part of the current element's subtree
def stump(e,anon):
    if len(anon)==0: return True
    else:
        return e[1]<anon[-1][0]
#traverse tree (make it into an actual tree)
def traverse(ll):
    if len(ll)==0: return (0,[])
    else:
        hd=ll[-1]
        ll.pop()
        nodes=[]
        while not stump(hd,ll):
            nodes.append(traverse(ll))
        return (hd[1]-hd[0]+1,nodes)
    
#process tree
def process_(anon):
    width,ll=anon
    #take away i dots, to create a need to fill in width-i dots using precomputed table
    takeAway=[0]*(width+1)
    if len(ll)==0: takeAway[0]=1
    #combine all retrieved arrays (dfs)
    else:
        retrieved=map(process_,ll)
        #map the head onto the thing
        for e in xrange(len(retrieved[-1])):
            takeAway[e]+=retrieved[-1][e]
        N_SQUARED=len(retrieved[-1])-1#optimization

        #combinations with the tail
        retrieved.pop()
        for e_ in retrieved:
            nn=[0]*len(takeAway)        #buffer
            for e in xrange(len(e_)):
                #for ee in xrange(len(nn)):
                for ee in xrange(N_SQUARED+1):#optimization
                    if e+ee<len(nn):
                        nn[e+ee]=(nn[e+ee]+e_[e]*takeAway[ee])%MOD
            takeAway=nn[:]
            N_SQUARED+=len(e_)-1#optimization
    #if the semicircle representing this node was not erased:
    #use precomputed table on each amount to find out num. ways
    acc=0
    for e in xrange(len(takeAway)):
        if width-e-2>=0:
            acc+=(takeAway[e]*fillGap[width-e-2])%MOD
    takeAway[width]=acc%MOD
    return takeAway
print process_(traverse(tree))[-1]

raw_input()
