import sys
def i(): return sys.stdin.readline().strip().split(" ")
_=map(int,i())
a,b,c,d,e,f=_[0],_[1],_[2],_[3],_[4],_[5]
row=2*a+1
ss=row
b-=1
f-=1
right,left=0,0
while c>0:
    if b==0:
        c-=1
        b-=1
    elif b==-1:
        c-=1
        right-=1
    else:
        b-=1
        right+=1
    if f==0:
        e-=1
        f-=1
    elif f==-1:
        e-=1
        left-=1
    else:
        f-=1
        left+=1
    ss+=row+left+right
print ss
