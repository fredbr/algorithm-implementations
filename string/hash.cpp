#include <bits/stdc++.h>

using namespace std;

using ll = long long;

class SHash {
private:
	static constexpr int nbases = 2;
	static constexpr ll bases[nbases] = {91, 107};
	static constexpr ll mods[nbases] = {1000000007, 1000000009};

	ll v[nbases];

public:
	SHash() {};
	SHash(string const& s)
	{
		fill(v, v+nbases, 0);
		for (int i = 0; i < nbases; ++i) {
			for (char a : s) {
				v[i] = (v[i]*bases[i] + a)%mods[i];	
			}
		}
	}

	bool operator==(SHash const& rhs) {
		for (int i = 0; i < nbases; i++) 
			if (v[i] != rhs.v[i]) return false;
		return true;
	}

	bool operator!=(SHash const& rhs) {
		for (int i = 0; i < nbases; i++) 
			if (v[i] == rhs.v[i]) return false;
		return true;
	}
};

int main()
{
	SHash x("fred"), y("fred");

	cout << (x==y) << "\n";
}