#include <bits/stdc++.h>

using namespace std;

string s, p;

vector<int> pre(string const& s)
{
    vector<int> err(s.size());
    err[0] = -1;
    int j = -1, m = s.size();

    for (int i = 0; i < m; i++)
    {
        while (j >= 0 && p[i] != p[j]) j = err[j];
        j++;
        err[i+1] = j;
    }

    return err;
}

vector<int> kmp(string const& s, string const& p, vector<int> const& err)
{
    int n = s.size(), m = p.size();
    vector<int> ans;

    int j = 0;
    for (int i = 0; i < n; i++)
    {
        while (j >= 0 && s[i] != p[j]) j = err[j];
        j++;
        if (j == m) ans.push_back(i-j+1), j = err[j];
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> s >> p;

    vector<int> err = pre(p);
    vector<int> ans =  kmp(s, p, err);

    for (int x : ans)
        cout << x << " ";
    cout << "\n";
}