import sys
import math
#import random
_=sys.stdin.readline().strip().split(" ")
n,h=int(_[0]),int(_[1])
field=[]
for e in xrange(n):
    _=sys.stdin.readline().strip().split(" ")
    #__=[random.randint(1,20) for ee in xrange(n)]
    __=[int(ee) for ee in _]
    field.append(__)
#def cross(x,y):
#    if x==n-1 and y==n-1:return True
#    else:
#        k=field[x][y]
#        field[x][y]=-1
#        if x-1>=0:
            #print math.fabs(k-field[x-1][y])
#            if field[x-1][y]<>-1 and (math.fabs(k-field[x-1][y])<=h):
#                if cross(x-1,y):return True
#        if x+1<n:
#            if field[x+1][y]<>-1 and (math.fabs(k-field[x+1][y])<=h):
#                if cross(x+1,y):return True
#        if y-1>=0:
#            if field[x][y-1]<>-1 and (math.fabs(k-field[x][y-1])<=h):
#                if cross(x,y-1):return True
#        if y+1<n:
#            if field[x][y+1]<>-1 and (math.fabs(k-field[x][y+1])<=h):
#                if cross(x,y+1):return True
#        return False
#if cross(0,0):print "yes"
#else:print "no"
points=[(0,0)]
while True:
    if len(points)==0:
        print "no"
        break
    elif (n-1,n-1) in points:
        print "yes"
        #for e in points:print e
        break
    Npoints=[]
    for e in range(len(points)):
        k=points[e]
        if field[k[0]][k[1]]<>-1:
            if k[0]-1>=0:
                if math.fabs(field[k[0]][k[1]]-field[k[0]-1][k[1]])<=h:
                    Npoints.append((k[0]-1,k[1]))
            if k[0]+1<n:
                if math.fabs(field[k[0]][k[1]]-field[k[0]+1][k[1]])<=h:
                    Npoints.append((k[0]+1,k[1]))
            if k[1]-1>=0:
                if math.fabs(field[k[0]][k[1]]-field[k[0]][k[1]-1])<=h:
                    Npoints.append((k[0],k[1]-1))
            if k[1]+1<n:
                if math.fabs(field[k[0]][k[1]]-field[k[0]][k[1]+1])<=h:
                    Npoints.append((k[0],k[1]+1))
            field[k[0]][k[1]]=-1
    points=Npoints[:]
