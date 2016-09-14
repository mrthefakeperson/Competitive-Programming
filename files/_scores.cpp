#include <bits/stdc++.h>

#define fst first
#define snd second
#define _ make_pair
#define push push_back
#define let auto

using namespace std;

int a,b,k,t;
int MOD=1000000007;
int ans[400005][205];
int main()
{
    scanf("%i%i%i%i",&a,&b,&k,&t);
    
    let c=2*k*t;
    ans[c][0]=1;
    for(let turn=1;turn<=2*t;turn++)
    {
        for(let e=0;e<=k;e++)
        {
            ans[c-k*turn][turn]=(ans[c-k*turn][turn]+ans[c-k*turn+e][turn-1])%MOD;
        }
        for(let e= -k*turn+1;e<=k*turn;e++)
        {
            let acc=(long long)ans[e+c-1][turn]+MOD;
            if(e-k-1>= -k*turn) acc-=ans[e+c-k-1][turn-1];
            if(e+k<=k*turn) acc+=ans[e+c+k][turn-1];
            ans[e+c][turn]=acc%MOD;
            /*
            ans[e+c][turn]=ans[e+c-1][turn];
            if(e-k-1>= -k*turn) ans[e+c][turn]=((long long)ans[e+c][turn]+MOD-ans[e+c-k-1][turn-1])%MOD;
            if(e+k<=k*turn) ans[e+c][turn]=(ans[e+c][turn]+ans[e+c+k][turn-1])%MOD;
                */
        }
    }
    
    let acc=0LL;
    for(let e=b-a+1;e<=k*2*t;e++)
        acc+=ans[e+c][2*t];
    printf("%I64d\n",acc%MOD);
    /*
    for(let e=0;e<=k*4*t;e++)
    {
        for(let ee=0;ee<=2*t;ee++)
        {
            printf("%i ",ans[e][ee]);
            //if(answer(e-2*k*t,ee)<0) while(1){}
        }
        printf("\n");
    }
*/
	return 0;
}
