def bs(l,a):
    r=[]
    for x in l:
        temp="B"+x+"S"
        if temp in a:
            r.append(temp)
    return r
def n(l,a):
    r=[]
    for x in l:
        for x2 in l:
            temp=x+"N"+x2
            if temp in a and temp not in l:
                r.append(temp)
    return r
def singleCheck(_i):
    aWords,loopTimes=["A"],0
    while _i not in aWords and loopTimes<=(len(_i)-1)/2:
        loopTimes+=1
        _1,_2=bs(aWords,_i),n(aWords,_i)
        aWords+=_1
        aWords+=_2
        #print len(aWords)
    return _i in aWords
_input,outList=raw_input(),""
while _input!="X":
    if singleCheck(_input): outList+="YES\n"
    else: outList+="NO\n"
    _input=raw_input()
print outList[:-1]
