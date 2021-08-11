#include <bits/stdc++.h>
using namespace std;

vector<int> buildSuffixArray(string &s)
{
	int n = s.length();
	vector<int> pos(n), sortt(n);
	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; i++)
	{
		a[i] = {s[i], i};
	}
	sort(a.begin(), a.end());
	for (int i = 0; i < n; i++)
	{
		pos[i] = a[i].second;
	}
	sortt[pos[0]] = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i].first == a[i - 1].first)
			sortt[pos[i]] = sortt[pos[i - 1]];
		else
			sortt[pos[i]] = sortt[pos[i - 1]] + 1;
	}
	vector<pair<pair<int, int>, int>> a_new(n);
	int k = 0;
	while ((1 << k) < n)
	{
		for (int i = 0; i < n; i++)
		{
			a_new[i] = {{sortt[i], sortt[(i + (1 << k)) % n]}, i};
		}
		sort(a_new.begin(), a_new.end());
		for (int i = 0; i < n; i++)
		{
			pos[i] = a_new[i].second;
		}
		sortt[pos[0]] = 0;
		for (int i = 1; i < n; i++)
		{
			if (a_new[i].first == a_new[i - 1].first)
				sortt[pos[i]] = sortt[pos[i - 1]];
			else
				sortt[pos[i]] = sortt[pos[i - 1]] + 1;
		}
		k++;
	}
	return pos;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif
	string s;
	cin >> s;
	s += '$';
	vector<int> position = buildSuffixArray(s);
	for (auto i : position)
	{
		cout << i << " ";
	}
}