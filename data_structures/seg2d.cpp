#include <bits/stdc++.h>

using namespace std;

int const maxn = 1001;

int n, m;
int v[maxn][maxn];

int op(int x, int y)
{
    return gcd(x, y);
}

class Seg
{
    int tree[1<<11][1<<11];

    void build_y(int nox, int noy, int lx, int rx, int ly, int ry)
    {
        if (ly == ry) {
            if (lx == rx) tree[nox][noy] = v[lx][ly];
            else tree[nox][noy] = op(tree[nox*2+1][noy], tree[nox*2+2][noy]);
        }
        else {
            int my = (ly+ry)/2;
            build_y(nox, noy*2+1, lx, rx, ly, my);
            build_y(nox, noy*2+2, lx, rx, my+1, ry);
            tree[nox][noy] = op(tree[nox][noy*2+1], tree[nox][noy*2+2]);
        }
    }

    void build_x(int nox, int lx, int rx)
    {
        if (lx != rx) {
            int mx = (lx+rx)/2;
            build_x(nox*2+1, lx, mx);
            build_x(nox*2+2, mx+1, rx);
        } 
        build_y(nox, 0, lx, rx, 1, m);
    }

    int get_y(int nox, int noy, int ly, int ry, int a, int b)
    {
        if (a <= ly and ry <= b) return tree[nox][noy];

        int my = (ly+ry)/2;

        if (b <= my) return get_y(nox, noy*2+1, ly, my, a, b);
        if (a > my) return get_y(nox, noy*2+2, my+1, ry, a, b);

        return op(get_y(nox, noy*2+1, ly, my, a, b),
                  get_y(nox, noy*2+2, my+1, ry, a, b));
    }

    int get_x(int nox, int lx, int rx, int a, int b, int ay, int by)
    {
        if (a <= lx and rx <= b) return get_y(nox, 0, 1, m, ay, by);

        int mx = (lx+rx)/2;

        if (b <= mx) return get_x(nox*2+1, lx, mx, a, b, ay, by);
        if (a > mx) return get_x(nox*2+2, mx+1, rx, a, b, ay, by);

        return op(get_x(nox*2+1, lx, mx, a, b, ay, by),
                  get_x(nox*2+2, mx+1, rx, a, b, ay, by));
    }

    void upd_y(int nox, int noy, int lx, int rx, int ly, int ry,
               int x, int y, int val)
    {
        if (ly == ry) {
            if (lx == rx) tree[nox][noy] = val;
            else tree[nox][noy] = op(tree[nox*2+1][noy], tree[nox*2+2][noy]);
        }
        else {
            int my = (ly+ry)/2;
            if (y <= my) upd_y(nox, noy*2+1, lx, rx, ly, my, x, y, val);
            else upd_y(nox, noy*2+2, lx, rx, my+1, ry, x, y, val);
            tree[nox][noy] = op(tree[nox][noy*2+1], tree[nox][noy*2+2]);
        }
    }

    void upd_x(int nox, int lx, int rx, int x, int y, int val)
    {
        if (lx != rx) {
            int mx = (lx+rx)/2;
            if (x <= mx) upd_x(nox*2+1, lx, mx, x, y, val);
            else upd_x(nox*2+2, mx+1, rx, x, y, val);
        }
        upd_y(nox, 0, lx, rx, 1, m, x, y, val);
    }

public:
    void build()
    {
        build_x(0, 1, n);
    }

    void upd(int x, int y, int val)
    {
        upd_x(0, 1, n, x, y, val);
    }

    int get(int lx, int rx, int ly, int ry)
    {
        return get_x(0, 1, n, lx, rx, ly, ry);
    }
};

int main()
{

}