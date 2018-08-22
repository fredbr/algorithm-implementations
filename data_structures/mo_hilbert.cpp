#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 100010;
const int sqt = 330;

inline int64_t ord(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = ord(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct query
{
	int l, r, id;
	ll w;

	bool operator<(const query &rhs) const {
		return w < rhs.w;
	}
};

int lim = 0;

struct bit
{
	int b[maxn];

	inline void add(int x, int d)
	{
		for (int i = x; i <= lim; i += i&-i) b[i] += d;
	}

	inline int get(int x)
	{
		int ans = 0;
		for (int i = x; i > 0; i -= i&-i) ans += b[i];
		return ans;
	}
};

bit re;
query qr[maxn];
int v[maxn], v2[maxn];

ll tot = 0;
ll sum = 0;

inline void addl(int x)
{	
	tot++;
	re.add(v[x], 1);
	sum += re.get(v[x]-1);
}

inline void addr(int x)
{
	tot++;
	re.add(v[x], 1);
	sum += tot - re.get(v[x]);
}

inline void reml(int x)
{
	tot--;
	re.add(v[x], -1);
	sum -= re.get(v[x]-1);
}

inline void remr(int x)
{
	tot--;
	re.add(v[x], -1);
	sum -= tot - re.get(v[x]);
}

ll res[maxn];



inline int readChar();
template <class T = int> inline T readInt(); 
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );

/** Read */

static const int buf_size = 4096;

inline int getChar() {
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, buf_size, stdin);
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar() {
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

template <class T>
inline T readInt() {
	char c = readChar();
	T x = 0;
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

template <class T> 
inline void writeInt( T x, char end ) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n--)
		writeChar(s[n]);
	if (end)
		writeChar(end);
}

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

struct Flusher {
	~Flusher() {
		if (write_pos)
			fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}
} flusher;



int main()
{
	int n;
	n = readInt();

	ll nn = 0;
	while ((1<<nn) < n) nn++;
	// cerr << nn << "\n";
	
	for (int i = 1; i <= n; i++) v[i] = readInt(), v2[i] = v[i];

	sort(v2+1, v2+1+n);
	lim = unique(v2+1, v2+1+n)-v2;
	
	for (int i = 1; i <= n; i++)
		v[i] = lower_bound(v2+1, v2+lim, v[i])-v2;

	int q;
	q = readInt();

	for (int i = 0; i < q; i++) {
		qr[i].l = readInt();
		qr[i].r = readInt();

		qr[i].w = ord(qr[i].l-1, qr[i].r-1, nn, 0);
		// qr[i].w = qr[i].l/sqt;
		qr[i].id = i;
	}

	sort(qr, qr+q);

	// ll dist = qr[0].l + qr[0].r;
	// for (int i = 1; i < q; i++)
	// 	dist += abs(qr[i].l-qr[i-1].l)+abs(qr[i].r-qr[i-1].r);

	// cerr << dist << "\n";

	int cl = 1, cr = 0;

	for (int i = 0; i < q; i++) {

		int l = qr[i].l, r = qr[i].r, id = qr[i].id;
		
		while (r > cr) addr(++cr);
		while (r < cr) remr(cr--);
		while (l < cl) addl(--cl);
		while (l > cl) reml(cl++);

		res[id] = sum;
	}

	for (int i = 0; i < q; i++) writeInt(res[i],'\n');

	return 0;
}