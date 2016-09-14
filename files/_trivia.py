import sys
#import random
#sys.setrecursionlimit(99999999)
def i(): return sys.stdin.readline().strip().split(" ")
_=i()
n,k=int(_[0]),int(_[1])
numbers=map(int,i())
#numbers=[random.randint(-1000000000,1000000000) for e in xrange(n)]
numbers.sort()
#numbers.append(numbers[-1])
diff=[numbers[0]]
for e in xrange(n-1):
    diff.append(numbers[e+1]-numbers[e])
diff.append(0)
addingOne=n%k
visited=[[0]*(k+1) for e in xrange(addingOne+1)]
for e in xrange(1,k+1):
    visited[0][e]=diff[0+e*(n/k)]+max(visited[0][e-1],0)
for a in xrange(1,addingOne+1):
    for b in xrange(a,k+1):
        #print a,b
        visited[a][b]=diff[a+b*(n/k)]+max(visited[a-1][b-1],visited[a][b-1])
print numbers[-1]-numbers[0]-visited[addingOne][k]
print visited
for e in xrange(0,addingOne+1):
    for ee in xrange(0,k+1):
        visited[e][ee]=0
def trivia(a,b):    #number of times n/k+1 was added, number of differences used
    if (a<0 or b<0) or a>b: return 0
    if a==0 and b==0: return 0
    if visited[a][b]==0:
        #print diff,a+b*(n/k)
        rr=diff[a+b*(n/k)]
        rr+=max(trivia(a-1,b-1),trivia(a,b-1))
        visited[a][b]=rr
    return visited[a][b]
print numbers[-1]-numbers[0]-(trivia(addingOne,k))
print visited
