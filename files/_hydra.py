import sys

def decrypt(key,string):
    rr=""
    for e in string:
        rr+=key[ord(e)-65]
    return rr

default=sys.stdin.readline().strip()
patterns,H,relevant={},[-10],[]
for e in xrange(len(default)):
    if default[e] in patterns:
        if e-patterns[default[e]]==4:
            H.append(patterns[default[e]])
        elif e-patterns[default[e]]==7 and H[-1]==e-8:
            relevant.append(default[H[-1]:H[-1]+9])

        #print H
        #print default[e],patterns[comp],e-patterns[comp]
    patterns[default[e]]=e
#print relevant

k,found=int(sys.stdin.readline().strip()),False

for e in xrange(k):
    crypt=sys.stdin.readline().strip()
    if decrypt(crypt,"HAILHYDRA") in relevant:
        rev,curr=[""]*26,65
        for e in crypt:
            rev[ord(e)-65]=chr(curr)
            curr+=1
        print decrypt(rev,default)
        found=True
        break

if not found:print"KeyNotFoundError"
