#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010101;

char s[maxn];
// bitset<maxn> s;
vector<int> primes;


void init()
{
	for (int i = 2; i*i < maxn; i++)
		if (!s[i]) 
			for (int j = i*i; j < maxn; j += i)
				s[j] = 1;

	for (int i = 2; i < maxn; i++)
		if (!s[i]) primes.push_back(i);
}

int main()
{
	init();
}