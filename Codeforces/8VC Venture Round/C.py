import sys
def i(): return sys.stdin.readline().strip()
sys.setrecursionlimit(99999999)
ii=lambda:map(int,i().split(" "))

a,b=ii()
a6=a/3*6+a%3*2
b6=b/2*6+b%2*3
#print a6,b6

e=6
while e<=a6 and e<=b6:
    e+=6
    #print a6,b6
    if a6+2<=b6+3:
        a6+=2
    else:
        b6+=3

print max(a6,b6)