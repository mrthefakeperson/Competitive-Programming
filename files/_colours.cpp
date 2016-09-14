#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

long long cost[105][105];
int colour[105];
long long best_tcb[105][105][105];
bool visited[105][105][105];
int trees,colours,target;
long long min_(long long a,long long b)
{
    if(a== -1) return b; else if(b== -1) return a; else return min(a,b);
}
long long answer(int t,int c,int b)
{
    //printf("%i,%i,%i\n",t,c,b);
    if(colour[t]!=0 && c!=colour[t]) return -1;
    if(t==0) return best_tcb[t][c][b];
    if(b==0) return -1;
    if(visited[t][c][b]) return best_tcb[t][c][b];
    visited[t][c][b]=true;
    
    let accMin= -1LL;
    for(let e=1;e<=colours;e++)
    {
        if(e!=c){
            accMin=min_(accMin,answer(t-1,e,b-1));
        }
    }
    accMin=min_(accMin,answer(t-1,c,b));
    if(colour[t]==0 && accMin!= -1) accMin+=cost[t][c];
    best_tcb[t][c][b]=accMin;
    //printf("%i,%i,%i -> %I64d\n",t,c,b,accMin);
    return accMin;
}
int main()
{
    //freopen("input.txt","r",stdin);
    scanf("%i%i%i",&trees,&colours,&target);
    for(let e=0;e<trees;e++)
    {
        scanf("%i",&colour[e]);
    }
    for(let e=0;e<trees;e++)
    {
        for(let ee=1;ee<=colours;ee++)
            scanf("%i",&cost[e][ee]);
    }
    for(let e=0;e<trees;e++)
    {
        for(let ee=1;ee<=colours;ee++)
        {
            for(let eee=0;eee<=target;eee++)
                best_tcb[e][ee][eee]= -1LL;
        }
    }
    if(colour[0]!=0){
        best_tcb[0][colour[0]][1]=0;
    }
    else{
        for(let e=1;e<=colours;e++)
            best_tcb[0][e][1]=cost[0][e];
    }
    let accMin=-1LL;
    for(let e=1;e<=colours;e++)
    {
        accMin=min_(accMin,answer(trees-1,e,target));
    }
    printf("%I64d\n",accMin);

	return 0;
}
