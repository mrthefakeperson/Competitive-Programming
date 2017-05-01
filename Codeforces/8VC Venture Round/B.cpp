#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

bool visited[405][405][405];
void src(int rr,int gg,int bb)
{
    if(!visited[rr][gg][bb]){
    visited[rr][gg][bb]=true;
    if(rr>0 && gg>0)
        src(rr-1,gg-1,bb+1);
    if(rr>0 && bb>0)
        src(rr-1,gg+1,bb-1);
    if(gg>0 && bb>0)
        src(rr+1,gg-1,bb-1);
    if(rr>1)
        src(rr-1,gg,bb);
    if(gg>1)
        src(rr,gg-1,bb);
    if(bb>1)
        src(rr,gg,bb-1);
    }
}
int main()
{
    int n;scanf("%i",&n);
    int r=0,g=0,b=0;
    for(int e=0;e<n;e++)
    {
        char c;scanf(" %c",&c);
        if(c=='R') r++;
        else if(c=='G') g++;
        else b++;
    }
    src(r,g,b);
    bool rr=false,gg=false,bb=false;
    for(int e=0;e<404;e++)
    {
        rr=rr || visited[e][0][0];
        gg=gg || visited[0][e][0];
        bb=bb || visited[0][0][e];
    }
    if(bb) printf("B");
    if(gg) printf("G");
    if(rr) printf("R");

	return 0;
}