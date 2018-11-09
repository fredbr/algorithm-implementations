#include <bits/stdc++.h>

using namespace std;

int main()
{
    bitset<100> bt;
    cin >> bt;

    cout << bt[0] << "\n";
    cout << bt.count() << "\n";
    cout << (~bt).none() << "\n";
    cout << (~bt).any() << "\n";
    cout << (~bt).all() << "\n";
    cout << bt._Find_first() << "\n";
    cout << bt._Find_next(10) << "\n";

    cout << bt << "\n";
}