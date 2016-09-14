class fractal:
    def __init__(self,wantedX,goalLength):
        self.x=wantedX
        self.l=goalLength
        self.current=["","",""]
    def printOut(self):
        for x in range(len(self.current)):
            self.k=float(self.x)/self.l*len(self.current)
            if int(self.k)==x or int(self.k)==x+1 or int(self.k)==x-1 or int(self.k)==x+2:
                print">  "+self.current[x]
            else:
                print "%2i %s"%(x,self.current[x])
    def trim(self):
        self.k=float(self.x)/self.l*len(self.current)
        for x in range(len(self.current)):
            if int(self.k)==x or int(self.k)==x+1 or int(self.k)==x-1 or int(self.k)==x+2:
                pass
            else:
                self.current[x]=""
    def retrieve(self):
        self.k=float(self.x)/self.l*len(self.current)
        #if self.x==self.l:
        #    return [1]
        self.count=[]
        self.left=self.current[int(self.k)-1]
        self.right=self.current[int(self.k)]
        #if (self.left+" ")[0]=="0" or (self.right+" ")[0]=="0":
        #    self.count.append(1)
        if len(self.left)>len(self.right):
            self.max=len(self.left)-1
        else:
            self.max=len(self.right)-1
        for ch in range(self.max+3):
            #print len("1"+self.left+"    "),ch
            if ("1"+self.left+"0"*81)[ch]!=("1"+self.left+"0"*81)[ch+1] or ("1"+self.right+"0"*81)[ch]!=("1"+self.right+"0"*81)[ch+1]:
                self.count.append(ch+1)
            #print "1"+self.right+"0000"
            #print ch
            #if self.left[ch]=="0" or self.right[ch]=="0":
                #self.count.append(ch+1)
        #if len(self.left)>len(self.right):
        #    self.count.append(len(self.right)+1)
        #    self.count.append(len(self.left)+1)
        #elif len(self.right)>len(self.left):
        #    self.count.append(len(self.left)+1)
        #    self.count.append(len(self.right)+1)
        #else:
        #    self.count.append(len(self.left)+1)
        return self.count
    def update(self):
        if self.current==["","",""]:
            self.current=["","1",""]
        else:
            newD=[]
            for x in range(len(self.current)):
                nextC,nextC2="",""
                for y in self.current[x]:
                    if y=="1":
                        nextC+="111"
                        nextC2+="111"
                    elif y=="0":
                        nextC+="010"
                        nextC2+="101"
                if x<len(self.current)/2:
                    newD.append(nextC)
                    newD.append(nextC2+"1")
                    newD.append(nextC+"01")
                elif x>len(self.current)/2:
                    newD.append(nextC+"01")
                    newD.append(nextC2+"1")
                    newD.append(nextC)
                else:
                    newD.append(nextC)
                    newD.append(nextC2+"1")
                    newD.append(nextC)
            self.current=newD
    def magnify(self):
        newD=[]#,nextC=""
        for line in self.current:
            nextC=""
            if len(line)>0:
                for e in line:
                    if e=="1":
                        nextC+="111"
                    else:
                        nextC+="000"
            newD.append(nextC)
            newD.append(nextC)
            newD.append(nextC)
        self.current=newD
_n=raw_input().split(" ")
level=int(_n[0])
width=int(_n[1])
target=int(_n[2])
frac=fractal(target,width)
for x in range(level):
    #print x
    frac.update()
    #frac.trim()
    #frac.printOut()
    #print len(frac.current)
while len(frac.current)<width:
    frac.magnify()
    #frac.printOut()
    #print "done",len(frac.current)
frac.printOut()
__k=frac.retrieve()
for e in __k:
    print e,
raw_input()
