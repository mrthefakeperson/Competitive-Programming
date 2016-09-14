k=input()
L=[]
for e in xrange(k):
    _=raw_input()
    L.append(_)
a=False
for e in xrange(k-2):
    if L[e+1]=="Bessarion":
        if (L[e]=="Leslie" and L[e+2]=="Bayview") or (L[e+2]=="Leslie" and L[e]=="Bayview"):
            a=True
if a:
    print "Y"
else:
    print "N"
