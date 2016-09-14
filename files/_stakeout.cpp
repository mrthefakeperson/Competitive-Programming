#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

const int SZ=1048576;
//const int SZ=64;
int buildings[300005], watched[300005], groupMin[SZ*2+5];
int groupOv[SZ*2+5];
int costs[300005];
int n,m;
void reset()
{
    for(let e=0;e<2*SZ;e++)
    {
        groupMin[e]=999999999;
        groupOv[e]=0;
    }
    for(let e=0;e<n;e++)
    {
        groupMin[SZ+e]=watched[e];
        let ee=SZ+e;
        while(ee>1)
        {
            groupMin[ee/2]=min(groupMin[ee/2],groupMin[ee]);
            ee/=2;
        }
    }
}
int get_min(pair<int,int> aa)
{
    //printf(">> %i,%i\n",aa.fst,aa.snd);
    let a=SZ+aa.fst,b=SZ+aa.snd-1;
    if(a>b) return 999999999;
    vector<pair<int,int> > as,bs;  //(node, overhead)
    while(a>0)
    {
        as.push(_(a,groupOv[a]));
        a/=2;
    }
    while(b>0)
    {
        bs.push(_(b,groupOv[b]));
        b/=2;
    }
    for(let e=(int)(as.size())-2;e>=0;e--)
    {
        as[e].snd+=as[e+1].snd;
        bs[e].snd+=bs[e+1].snd;
    }
    let accMin=min(groupMin[as[0].fst]+as[1].snd,groupMin[bs[0].fst]+bs[1].snd);
    for(let e=0;e<(int)(as.size())-1 && bs[e].fst-as[e].fst>1;e++)
    {
        if(as[e].fst%2==0){
            accMin=min(accMin,groupMin[as[e].fst+1]+as[e+1].snd);
        }
        if(bs[e].fst%2==1){
            accMin=min(accMin,groupMin[bs[e].fst-1]+bs[e+1].snd);
        }
    }
    return accMin;
}
void changeR(int exclBound,int v)
{
    let e=SZ+exclBound;
    while(e>1)
    {
        if(e%2==1){
            groupOv[e-1]+=v;
            groupMin[e-1]+=v;
        }
        groupMin[e/2]=groupOv[e/2]+min(groupMin[e/2*2],groupMin[e/2*2+1]);
        e/=2;
    }
}
void printAll()
{
    for(let e=0;e<n;e++)
    {
        let ee=SZ+e,acc=groupMin[SZ+e]-groupOv[SZ+e];
        while(ee>0)
        {
            acc+=groupOv[ee];
            ee/=2;
        }
        printf("%i, ",acc);
    }
    printf("\n");
}
void decr(pair<int,int> aa)
{
    changeR(aa.fst,1);
    changeR(aa.snd,-1);
}
int main()
{
    //freopen("input.txt","r",stdin);
    
    int q;scanf("%i%i%i",&n,&m,&q);
    costs[0]=2;
    for(let e=1;e<m;e++) costs[e]=(costs[e-1]*2)%1000000007;
    for(let e=0;e<n;e++) scanf("%i",&buildings[e]);
    stable_sort(buildings,buildings+n);
    vector<pair<int,int> > agents;
    for(let e=0;e<m;e++)
    {
        int p,r;
        scanf("%i%i",&p,&r);
        int s=lower_bound(buildings,buildings+n,p-r)-buildings, d=lower_bound(buildings,buildings+n,p+r+1)-buildings;
        agents.push(_(s,d));
        watched[s]++;
        watched[d]--;
    }
    for(let e=1;e<n;e++)
        watched[e]+=watched[e-1];
    for(let ___=0;___<q;___++)
    {
        reset();
        //printAll();
        int a;scanf("%i",&a);
        if(get_min(_(0,n))<a){
            printf("-1\n");
        }
        else{
            let acc=0;
            for(let e=m-1;e>=0;e--)
            {
                let got_min=get_min(agents[e]);
                if(got_min>a){
                    decr(agents[e]);
                }
                else{
                    acc+=costs[e];
                    acc%=1000000007;
                }
                //printf("%i:  ",e);printAll();
                //printf(" -> %i\n",got_min);
            }
            printf("%i\n",acc);
        }
    }

	return 0;
}
