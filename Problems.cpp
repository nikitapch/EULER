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
set<int> q_odd;
vector<vector<pii> > g(N);
vector<int> order(N);
bool mark[4 * N], used[4 * N], ex;
int deg[N], cnt, csc;

void dfs(int v)
{
	if (ex)
		return;
	if (deg[v] & 1)
	{

		bool ok = false;
		pii u = mp(-1, -1);

		for (auto to : g[v])
		if (!used[to.x])
		{
			if (deg[to.y] & 1)
			{
				ok = true;
				u = to;
				break;
			}
			if (deg[to.y] > 0)
				u = to;
		}

		q_odd.erase(v);
		if (ok || u.x != -1 && !ok)
		{
			deg[v]--;
			deg[u.y]--;
			if (ok)
				q_odd.erase(u.y);
			else
				q_odd.insert(u.y);
			used[u.x] = true;
			if (!csc)
				cout << v << " ";
			cout << u.y << " ";
			csc++;
			if (ok)
			{
				ex = true;
				return;
			}
		}

		if (!used[u.x])
			dfs(u.y);
	}
	for (auto to : g[v])
		if (!used[to.x])
			dfs(to.y);
}

int main()
{
	int v, n, m, x, y, k, u;
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
			q_odd.insert(i);

	k = sz(q_odd);

	if (!q_odd.empty())
		v = *q_odd.begin();

	//cout << v << endl;
	cout << (k / 2 <= 1 ? 1 : k / 2) << endl;

	while (sz(q_odd) > 2)
	{
		ex = false;
		csc = 0;
		dfs(*q_odd.begin());
		cout << endl;
	}

	v = 1;
	if (!q_odd.empty())
	{
		v = *q_odd.begin();
		u = *q_odd.rbegin();
		g[v].pb(mp(++cnt, u));
		g[u].pb(mp(cnt, v));
	}

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
			order.pb(u);
		}
	}
	
	forn(i, sz(order) - (sz(q_odd) > 0))
		cout << order[i] << " ";

	system("pause");

	return 0;
}