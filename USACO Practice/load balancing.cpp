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
#define let auto

using namespace std;

const int SQ=500;
pair<int,int> points[100005];    //
int n;

int main()
{
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    int n;scanf("%i",&n);
    for(let e=0;e<n;e++)
    {
        int a,b;scanf("%i%i",&a,&b);
        points[e]=_(a,b);
    }
    let accMin=n;
    for(let e=0;e<n;e++)
    {
        let el=points[e];
        let _1=0,_2=0,_3=0,_4=0;
        for(let ee=0;ee<n;ee++)
        {
            let itm=points[ee];
            if(itm.fst<=el.fst && itm.snd<=el.snd) _1++;
            else if(itm.fst<=el.fst && itm.snd>el.snd) _2++;
            else if(itm.fst>el.fst && itm.snd>el.snd) _3++;
            else _4++;
        }
        //printf("%i  %i  %i  %i\n",ans[e],a2[e],a3[e],a4[e]);
        accMin=min(accMin,max(max(_1,_2),max(_3,_4)));
    }
    printf("%i\n",accMin);

	return 0;
}