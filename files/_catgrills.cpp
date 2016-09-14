#include <cstdio>
#include <vector>
#include <algorithm>
#define push push_back
#define pop pop_back
#define fst first
#define snd second
using namespace std;
/*
int lastOf(vector<int> vv)
{
	return vv[vv.size()-1];
}*/
vector<long long> grillsP, grillsC;
int find(long long what)
{
	int place = 0, jump = grillsP.size();
	while (jump>1)
	{
		//printf("%i\n", place);
		jump /= 2;
		if (grillsP[place] == what) break;
		else if (what > grillsP[place + jump]){
			place += jump;
		}
	}
	while (grillsP[place] >= what) place--;
	while (grillsP[place] < what) place++;
	//printf("%i\n", place);
	return place;
}
//long long view, q, nextCute, nextPose, nexxt;
int main()
{
	//vector<int> v_; v_.push(1); v_.push(2); v_.push(3); v_.push(5);
	//printf("%i   %i\n", find(v_, 2), find(v_, 4));

	long long view, q; scanf("%lld%lld", &q, &view);
	vector<long long> ans; ans.push(0);
	grillsP.push(0); grillsC.push(0);
	long long nextCute, nextPose, nexxt; int foundPlace;
	//int accCute=0,accFat=0,leftCat=0;
	for (long long e = 0; e < q; e++)
	{
		char op; scanf(" %c", &op);
		if (op == 'D'){
			grillsP.pop(); grillsC.pop();
			ans.pop();
			//printf("%i\n", lastOf(ans));
		}
		else{
			
			scanf("%lld%lld", &nextPose, &nextCute);
			nextPose += grillsP[grillsP.size()-1]; nextCute += grillsC[grillsC.size()-1];
			grillsP.push(nextPose); grillsC.push(nextCute);
			if (nextPose - view <= 0) foundPlace = 0;
			else foundPlace = find(nextPose - view);
			nexxt = max(ans[ans.size()-1], nextCute - grillsC[foundPlace]);
			//printf("nextCute:%i     subtracted %i at %i      ", nextCute,grillsC[foundPlace],foundPlace);
			//printf("last:%i   new:%i\n", lastOf(ans), nextCute - grillsC[foundPlace]);
			printf("%lld\n", nexxt);
			ans.push(nexxt);
		}
	}
	//scanf(" ");
	return 0;
}