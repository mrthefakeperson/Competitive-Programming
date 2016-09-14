import sys
def i(): return sys.stdin.readline().strip().split(" ")

def checkSet(word):
    if len(word)<=1:return False
    else:
        if word[-2:]=="'s":
            return True
        else:
            return False
n=input()
for e in xrange(n):
    __=i()
    _=[e.lower() for e in __]
    if checkSet(_[0]):
        print "Set"
    else:
        if _[0]=="damaged": print "Normal"
        else:
            if len(_)>4: print "Normal"
            elif len(_)>2:
                if _[-2]=="of":
                    print "Magic"
                else:
                    print "Normal"
            elif len(_)==2:
                if _[0]=="of":
                    print "Rare"
                else:
                    print "Not sure, take anyways"
            else:print "Normal"
