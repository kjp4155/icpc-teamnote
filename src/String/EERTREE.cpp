#include<cstdio>
#include<algorithm>
#include<iostream>
#include<string>
#include<memory.h>
using namespace std;

const int maxn = 5e5 + 1, sigma = 26;
int len[maxn], link[maxn], to[maxn][sigma];
int ans[maxn][2];
int slink[maxn], diff[maxn], series_ans[maxn][2];
int sz, last, n;
char s[maxn];

void init()
{
    s[n++] = -1;
    link[0] = 1;
    len[1] = -1;
    sz = 2;
}

int get_link(int v)
{
    while (s[n - len[v] - 2] != s[n - 1]) v = link[v];
    return v;
}

void add_letter(char c)
{
    s[n++] = c -= 'a';
    last = get_link(last);
    if (!to[last][c])
    {
        len[sz] = len[last] + 2;
        link[sz] = to[get_link(link[last])][c];
        diff[sz] = len[sz] - len[link[sz]];
        if (diff[sz] == diff[link[sz]])
            slink[sz] = slink[link[sz]];
        else
            slink[sz] = link[sz];
        to[last][c] = sz++;
    }
    last = to[last][c];
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();
    string s;
    cin >> s;
    int n = s.size();
    memset(ans, 63, sizeof(ans));
    ans[0][0] = 0;
    ans[0][1] = 1e9;
    for (int i = 1; i <= n; i++)
    {
        add_letter(s[i - 1]);
        for (int v = last; len[v] > 0; v = slink[v])
        {
            series_ans[v][0] = ans[i - (len[slink[v]] + diff[v])][0];
            series_ans[v][1] = ans[i - (len[slink[v]] + diff[v])][1];
            if (diff[v] == diff[link[v]]) {
                series_ans[v][0] = min(series_ans[v][0], series_ans[link[v]][0]);
                series_ans[v][1] = min(series_ans[v][1], series_ans[link[v]][1]);
            }
            ans[i][1] = min(ans[i][1], series_ans[v][0] + 1);
            ans[i][0] = min(ans[i][0], series_ans[v][1] + 1);
        }
        int res = max(0, i + 2 - ans[i][0]) / 2 + max(0, i + 2 - ans[i][1]) / 2;
        cout << res << "\n";
    }
}
