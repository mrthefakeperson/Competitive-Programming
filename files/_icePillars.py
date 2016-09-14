import sys
p=int(sys.stdin.readline().strip())-1
pillar=map(int,sys.stdin.readline().strip().split(" "))
opt1,opt2=(pillar[0],pillar[0]),(pillar[0],pillar[0])       #amt spent on last pillar,amt total
for e in xrange(p):
    preOpt1,preOpt2=opt1,opt2
    nextPillar=map(int,sys.stdin.readline().strip().split(" "))
    amtSpent1=max(0,nextPillar[0]-pillar[1])
    opt1=(amtSpent1,min(opt1[1]+amtSpent1,opt2[1]+amtSpent1))
    amtSaved1=min(opt2[0],nextPillar[1])
    opt2_1=(nextPillar[0],preOpt2[1]-amtSaved1+nextPillar[0])
    amtSaved2=min(preOpt1[0],nextPillar[1])
    opt2_2=(nextPillar[0],preOpt1[1]-amtSaved2+nextPillar[0])
    opt2=(nextPillar[0],min(opt2_1[1],opt2_2[1]))
    #print opt1,opt2
    pillar=nextPillar[:]
print min(opt1[1],opt2[1])
