#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define fst first
#define snd second
#define _ make_pair
#define push push_back

using namespace std;
bool stuff[2005][5005];
int buffer[5005][2005];
int variation[2005][2005];
int n, m;

void radixSort(int lBound, int rBound, int ind)
{
	if (lBound <= rBound){
		//printf("%i %i ind %i\n", lBound, rBound, ind);
		//for (int e = 0; e < n; e++) printf("%i  ", buffer[ind][e]);
		//printf("\n");
		int ll = lBound, rr = rBound;
		for (int e = lBound; e <= rBound; e++)
		{
			if (stuff[buffer[ind][e]][ind]){
				//buffer[!(ind % 2)][rr] = buffer[ind % 2][e];
				buffer[ind + 1][rr] = buffer[ind][e];
				rr--;
			}
			else{
				//buffer[!(ind % 2)][ll] = buffer[ind % 2][e];
				buffer[ind + 1][ll] = buffer[ind][e];
				ll++;
			}
		}
		if (ind < m - 1){
			radixSort(lBound, rr, ind + 1);
			radixSort(ll, rBound, ind + 1);
		}
	}
}

int thing[2005];

int main()
{
	scanf("%i%i", &n, &m);
	for (int e = 0; e < n; e++)
	{
		for (int ee = 0; ee < m; ee++)
		{
			char chr = getchar();
			while (chr != '1' && chr != '0') chr = getchar();
			stuff[e][ee] = chr == '1';
		}
	}
	for (int e = 0; e < n; e++)
	{
		buffer[0][e] = e;
		//thing[e] = e;   no
	}
	radixSort(0, n - 1, 0);

	//for (int e = 0; e < n; e++) printf("%i  ", buffer[0][e]);
	for (int e = 0; e < n; e++)
	{
		//thing[e] = buffer[m][e];
		thing[buffer[m][e]] = e;
	}

	for (int e = 0; e < n; e++)
	{
		int accMin = 10000;
		for (int ee = e - 1; ee >= 0; ee--)
		{
			if (ee == e - 1){  //find it
				for (int e_ = 0; e_ < m; e_++)
				{
					if (stuff[buffer[m][e]][e_] != stuff[buffer[m][ee]][e_]){
						if (e_ == 0) accMin = 0;
						break;
					}
					accMin = e_ + 1;
				}
			}
			else{  //do stuff
				accMin = min(accMin, variation[ee][ee + 1]);
			}
			variation[ee][e] = accMin;
		}
	}
	/*
	for (int e = 0; e < n; e++)
	{
		for (int ee = 0; ee < n; ee++)
		{
			printf("%i  ", variation[e][ee]);
		}printf("\n");
	}
	*/
	int q; scanf("%i", &q);
	for (int e = 0; e < q; e++)
	{
		int a, b; scanf("%i%i", &a, &b); a--; b--;
		
		//for (int e = 0; e < n; e++) printf("%i  ", thing[e]);
		//printf("\n");
		
		if (a == b) printf("%i\n", m);
		else{
			//get
			int accMin = 10000;
			for (int e = a; e < b; e++)
			{
				int m1 = min(thing[e], thing[e + 1]), m2 = max(thing[e], thing[e + 1]);
				accMin = min(accMin, variation[m1][m2]);
			}
			printf("%i\n", accMin * (b - a + 1));
			//swap
			int middleMan;
			middleMan = thing[a];
			thing[a] = thing[b];
			thing[b] = middleMan;
		}
	}

	scanf(" ");
	return 0;
}