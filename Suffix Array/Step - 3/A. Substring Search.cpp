#include <bits/stdc++.h>
using namespace std;

void radix_sort(vector < pair<pair<int, int>, int> > &a)
{
	int n = a.size();
	vector<int> count(n), p(n);
	for (int i = 0; i < n; i++)
	{
		count[a[i].first.second]++;
	}
	p[0] = 0;
	for (int i = 1; i < n; i++)
	{
		p[i] = p[i - 1] + count[i - 1];
	}
	vector<pair<pair<int, int>, int>> a_new(n);
	for (auto i : a)
	{
		int x = i.first.second;
		a_new[p[x]] = i;
		p[x]++;
	}
	a = a_new;
	count.resize(0);
	count.resize(n);
	for (int i = 0; i < n; i++)
	{
		count[a[i].first.first]++;
	}
	p[0] = 0;
	for (int i = 1; i < n; i++)
	{
		p[i] = p[i - 1] + count[i - 1];
	}
	for (auto i : a)
	{
		int x = i.first.first;
		a_new[p[x]] = i;
		p[x]++;
	}
	a = a_new;
}

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
		radix_sort(a_new);
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

bool binarySearch(string &s, vector<int> &p, string &check)
{
	int n = s.size();
	int l = 0, r = n - 1;
	bool found = false;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (check == s.substr(p[mid], min((int)check.size(), n - p[mid])))
		{
			found = true;
			break;
		}
		if (check > s.substr(p[mid], min((int)check.size(), n - p[mid])))
		{
			l = mid + 1;
		}
		else
		{
			r = mid - 1;
		}
	}
	return found;

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
	int q;
	cin >> q;
	while (q--)
	{
		string check;
		cin >> check;
		int start = binarySearch(s, position, check);
	}
}