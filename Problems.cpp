// Problems.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <queue>
#include <set>
#include <algorithm>
#include <stack>
#include <vector>

#define x first
#define y second
#define mp make_pair
#define sqr(x) ((x) * (x))
#define pb push_back
#define all(c) c.begin(), c.end()
#define sz(c) int((c).size())
#define forn(i, n) for(int i = 0; i < int(n); i++)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll N = 5e5 + 9, M = 2e3 + 11, INF = 1e9 + 7, INF64 = 1e15 + 7;
const ld EPS = 1e-10;

stack<int> q;
vector<vector<pii> > g(N);
vector<vector<int> > order(N);
bool mark[4 * N], used[4 * N];
int deg[N], cnt, st, csc;

void dfs(int v)
{
	mark[v] = true;
	if (st <= 2)
		return;
	if (deg[v] & 1)
	{
		pii u = mp(-1, -1);
		int tt;
		bool ok = false;
		for (auto to : g[v])
		{
			if (deg[to.y] & 1)
			{
				deg[v]--;
				deg[to.y]--;
				st -= 2;
				used[to.x] = true;
				if (sz(order[csc]) == 0)
				{
					order[csc].pb(v);
					order[csc].pb(to.y);
				}
				else
					order[csc].pb(to.y);
				csc++;
				tt = to.y;
				ok = true;
				break;
			}
			if (deg[to.y] > 0)
				u = to;
		}
		if (ok && !mark[tt])
			dfs(tt);
		if (!ok && u.x != -1)
		{
			deg[v]--;
			deg[u.y]--;
			used[u.x] = true;
			if (sz(order[csc]) == 0)
			{
				order[csc].pb(v);
				order[csc].pb(u.y);
			}
			else
				order[csc].pb(u.y);
			if (!mark[u.y])
				dfs(u.y);
		}
	}
	for (auto to : g[v])
		if (!mark[to.y])
			dfs(to.y);
}

int main()
{
	ll k2 = 1;
	int v, n, m, x, y, ans;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;

	forn(i, m)
	{
		cin >> x >> y;
		g[x].pb(mp(++cnt, y));
		g[y].pb(mp(cnt, x));
		deg[x]++;
		deg[y]++;
	}
	
	v = 1;

	for (int i = 1; i <= n; i++)
		if (deg[i] & 1)
		{
			st++;
			v = i;
		}
	
	//cout << cnt << endl;
	ans = st;

	cout << v << endl;
	ans = ans / 2 <= 1 ? 1 : ans / 2;
	cout << ans << endl;

	dfs(v);

	v = 1;
	for (int i = 1; i <= n; i++)
		if (deg[i] & 1)
			v = i;

	q.push(v);


	while (!q.empty())
	{
		int u = q.top();
		bool ok = false;
		for (auto to : g[u])
			if (!used[to.x])
			{
				q.push(to.y);
				ok = true;
				used[to.x] = true;
				break;
			}
		if (!ok)
		{
			q.pop();
			cout << u << " ";
		}
	}
	cout << endl;

	//just comment
	//just comment2
	//just comment3
	//just more one comment

	forn(i, csc)
	{
		for (auto x : order[i])
			cout << x << " ";
		cout << endl;
	}
	system("pause");

    return 0;
}