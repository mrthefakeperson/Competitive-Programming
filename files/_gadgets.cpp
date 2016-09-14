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

int dlr[200005],pnd[200005];
int dlrDay[200005],pndDay[200005];
vector<pair<int,int> > g1i,g2i;
vector<int> gadgets1,gadgets2;
vector<long long> sumG1,sumG2;
bool sorter(pair<int,int> a,pair<int,int> b){return a.fst<b.fst;}
int find_(vector<int> * gadgets,long long proposed,int factor)
{
    int place= -1,jump= (*gadgets).size();
    while(jump>0)
    {
        if(place+jump<(*gadgets).size() && (long long)(*gadgets)[place+jump]*factor<=proposed)
            place+=jump;
        jump/=2;
    }
    while(place+1<(*gadgets).size() && (long long)(*gadgets)[place+1]*factor<=proposed) place++;
    return place+1;
}
bool good(long long proposed,int convertD,int convertP,int av)
{
    if(proposed>1000000000000LL) return false;
    int pl1= find_(&gadgets1,proposed,convertD);
    int pl2= find_(&gadgets2,proposed,convertP);
    return sumG1[pl1]*convertD+sumG2[pl2]*convertP<=av;
}
pair<int,int> take(long long proposed,int convertD,int convertP,long long t)
{
    int pl1= find_(&gadgets1,proposed,convertD);
    int pl2= find_(&gadgets2,proposed,convertP);
    let a=sumG1[pl1]*convertD+sumG2[pl2]*convertP;
    let mny=t-a;
    while(mny>=0)
    {
        if(pl1>=gadgets1.size() && pl2>=gadgets2.size()) break;
        else if(pl1>=gadgets1.size()){
            mny-=(long long)gadgets2[pl2]*convertP;
            if(mny<0) break;
            pl2++;
        }
        else if(pl2>=gadgets2.size()){
            mny-=(long long)gadgets1[pl1]*convertD;
            if(mny<0) break;
            pl1++;
        }
        else if(gadgets1[pl1]*convertD<gadgets2[pl2]*convertP)
        {
            mny-=(long long)gadgets1[pl1]*convertD;
            if(mny<0) break;
            pl1++;
        }
        else{
            mny-=(long long)gadgets2[pl2]*convertP;
            if(mny<0) break;
            pl2++;
        }
    }
    return _(pl1,pl2);
}
int main()
{
    int days,gadgets,needed,moneys;scanf("%i%i%i%i",&days,&gadgets,&needed,&moneys);
    dlr[0]=9999999;pnd[0]=9999999;
    for(let e=0;e<days;e++)
    {
        scanf("%i",&dlr[e+1]);
        dlrDay[e+1]=e+1;
        if(dlr[e+1]>dlr[e]){
            dlr[e+1]=dlr[e];
            dlrDay[e+1]=dlrDay[e];
        }
    }
    for(let e=0;e<days;e++)
    {
        scanf("%i",&pnd[e+1]);
        pndDay[e+1]=e+1;
        if(pnd[e+1]>pnd[e]){
            pnd[e+1]=pnd[e];
            pndDay[e+1]=pndDay[e];
        }
    }
    for(let e=0;e<gadgets;e++)
    {
        int a,b;scanf("%i%i",&a,&b);
        if(a==1){
            gadgets1.push(b);
            g1i.push(_(b,e+1));
            //sumG1.push(sumG1[sumG1.size()-1]+b);
        }
        else{
            gadgets2.push(b);
            g2i.push(_(b,e+1));
            //sumG2.push(sumG2[sumG2.size()-1]+b);
        }
    }
    sort(gadgets1.begin(),gadgets1.end());
    sort(gadgets2.begin(),gadgets2.end());
    sort(g1i.begin(),g1i.end(),sorter);
    sort(g2i.begin(),g2i.end(),sorter);
    sumG1.push(0);sumG2.push(0);
    for(int e:gadgets1) sumG1.push(sumG1[sumG1.size()-1]+e);
    for(int e:gadgets2) sumG2.push(sumG2[sumG2.size()-1]+e);

    let fl=false;
    for(let e=1;e<=days;e++)
    {
        let place=0LL; //most money that can be spent on one single item this day
        let jump=1000000000000LL;
        while(jump>0)
        {
            if(good(place+jump,dlr[e],pnd[e],moneys)){
                place+=jump;
            }
            jump/=2;
        }
        while(good(place+1,dlr[e],pnd[e],moneys)) place++;
        //if(find_(&gadgets1,place,dlr[e])+find_(&gadgets2,place,pnd[e])>=needed){
        auto aa=take(place,dlr[e],pnd[e],moneys);
        if(aa.fst+aa.snd>=needed){
            printf("%i\n",e);
            int pl1= aa.fst;
            int pl2= aa.snd;
            int acc=0;
            for(let ee=0;ee<pl1 && acc<needed;ee++)
            {
                printf("%i %i\n",g1i[ee].snd,dlrDay[e]);acc++;
            }
            for(let ee=0;ee<pl2 && acc<needed;ee++)
            {
                printf("%i %i\n",g2i[ee].snd,pndDay[e]);acc++;
            }
            fl=true;
            break;
        }
    }
    if(!fl) printf("-1\n");

	//scanf(" ");
	return 0;
}
