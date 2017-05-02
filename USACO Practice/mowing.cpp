#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

#define fst first
#define snd second
#define _ make_pair
#define push push_back

using namespace std;

vector<pair<pair<int,int>,pair<int,int> > > segments;
int intersect(pair<pair<int,int>,pair<int,int> > a,pair<pair<int,int>,pair<int,int> > b)
{
    bool aV=a.fst.fst==a.snd.fst,bV=b.fst.fst==b.snd.fst;
    if(aV==bV) return 0;
    else{
        if(aV){
            bool _1= (a.fst.fst>b.fst.fst && a.fst.fst<b.snd.fst) || (a.fst.fst<b.fst.fst && a.fst.fst>b.snd.fst);
            bool _2= (b.fst.snd>a.fst.snd && b.fst.snd<a.snd.snd) || (b.fst.snd<a.fst.snd && b.fst.snd>a.snd.snd);
            return _1 && _2;
        }
        else{
            bool _1= (b.fst.fst>a.fst.fst && b.fst.fst<a.snd.fst) || (b.fst.fst<a.fst.fst && b.fst.fst>a.snd.fst);
            bool _2= (a.fst.snd>b.fst.snd && a.fst.snd<b.snd.snd) || (a.fst.snd<b.fst.snd && a.fst.snd>b.snd.snd);
            return _1 && _2;
        }
    }
}
int main()
{
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);

    int n,t;scanf("%i%i",&n,&t);
    int a,b;scanf("%i%i",&a,&b);
    long long acc=0;
    for(int e=0;e<n-1;e++)
    {
        int c,d;scanf("%i%i",&c,&d);
        segments.push(_(_(a,b),_(c,d)));
        a=c;
        b=d;
        for(int ee=0;ee<e-t;ee++)
        {
            acc+=intersect(segments[ee],segments[e]);
        }
    }
    printf("%lld\n",acc);

	return 0;
}