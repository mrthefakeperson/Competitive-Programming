#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

const int SQ=500;
long long volumes[100005];
long long sortedV[100005];int legend[100005];
vector<pair<long long,long long> > groups[400];
long long maxStored[400];
long long getMaxUpTo(long long v,int group)
{
    long long accMax=0;
    for(int e=0;e<group;e++)
    {
        accMax=max(accMax,maxStored[e]);
    }
    for(auto p:groups[group])
    {
        if(p.fst<v){
            accMax=max(accMax,p.snd);
        }
    }

    groups[group].push(_(v,accMax+v));
    maxStored[group]=max(maxStored[group],   accMax+v);
    return accMax+v;
}
int main()
{
    int n;scanf("%i",&n);
    for(int e=0;e<n;e++)
    {
        int a,b;scanf("%i%i",&a,&b);
        volumes[e]=(long long)a*a*b;
        sortedV[e]=volumes[e];
    }/*
    for(int e=0;e<n;e++)
        printf("%I64d ",volumes[e]);
    printf("\n");*/
    sort(sortedV,sortedV+n);
    for(int e=0;e<n;e++)
    {
        legend[e]=e/SQ;
    }
    long long accMax=0;
    for(int e=0;e<n;e++)
    {
        long long n_=getMaxUpTo(volumes[e],legend[lower_bound(sortedV,sortedV+n,volumes[e])-sortedV]);
        //printf("%I64d\n",n_);
        accMax=max(accMax,n_);
    }
    //printf("%I64d\n",accMax);
    double pi = 3.1415926535897;
    printf("%.8f\n",pi*(double)accMax);

	return 0;
}