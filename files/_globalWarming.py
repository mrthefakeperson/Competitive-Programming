def sequence(L):
    for x in range(len(L)):
        compList=[]
        while len(compList)<len(L):
            compList+=L[:x+1]
            #print len(compList),len(L)
            #print compList
        if compList[:len(L)]==L: return x+1
def count(L):
    if len(L)==1: return 0
    newList=[]
    for x in range(len(L)-1):
        newList.append(int(L[x+1])-int(L[x]))
    return sequence(newList)
_i,final=raw_input(),""
while _i[0]!="0":
    _ii=_i.split()[1:]
    #print _ii
    final+=str(count(_ii))+"\n"
    _i=raw_input()
print final[:-1]
