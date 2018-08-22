#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
// double tambem funciona na maioria dos casos

typedef long long ll;

struct line
{
	char type;
	// type = 0 : linha do envelope
	// type = 1 : query no x (interseccao das linha) no envelope

	ld x;
	// x das interseccoes

	ll m, b;
	// m : coeficiente angular
	// b : constante
};

bool operator< (const line &a, const line &b)
{
	if (a.type + b.type > 0) return a.x < b.x;
	return a.m > b.m; 
	// para maximo inverter o  sinal do ultimo return
}

typedef set<line>::iterator sit;
set<line> env;

bool has_prev(sit it)
{
	return (it != env.begin());
}

bool has_next(sit it)
{
	return (it != env.end() and ++it != env.end());
}

bool bad(line i, line j, line k)
{
	return (k.b-i.b)*(i.m-j.m) < (j.b-i.b)*(i.m-k.m);
	// para maximo inverter o sinal
}

ld intersect(sit i, sit j)
{
	return (ld)(i->b-j->b)/(j->m-i->m);
}

void calc_x(sit i)
{
	if (has_prev(i)) {

		line l = *i;

		l.x = intersect(prev(i), i);
		env.erase(i);
		env.insert(l);
	}
}

void add(ll m, ll b)
{
	sit it;

	line l = {0, 0, m, b}; 

	it  = env.lower_bound(l);


	// checa linhas colineares
	if (it != env.end() and it->m == m)
	{
		if (it->b <= b) env.erase(it);
		else return;
	}

	env.insert(l);
	it = env.find(l);

	// checa se a linha colocada deve ser removida
	if (has_prev(it) and has_next(it) and bad(*prev(it), *it, *next(it))) {

		env.erase(it);
		return;
	}

	// retira linhas da direta irrelevantes
	while (has_next(it) and has_next(next(it)) and bad(*it, *next(it), *next(next(it))))
		env.erase(next(it));

	// retira linhas da esquerda irrelevantes
	while (has_prev(it) and has_prev(prev(it)) and bad(*prev(prev(it)), *prev(it), *it))
		env.erase(prev(it));

	// salva o x das interseccoes dele com o anterior e o proximo
	if (has_next(it)) calc_x(next(it));
	calc_x(it);
}

ll query(ll x)
{
	sit it = env.upper_bound({1, (ld)x, 0, 0});
	it--;

	return it->m*x + it->b;
}

int main()
{

}