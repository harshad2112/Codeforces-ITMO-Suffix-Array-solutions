#include <bits/stdc++.h>
using namespace std;

class segmentTree {
    vector<long long> tree;
    int left, right, siz;
public:
    segmentTree(vector<int> &arr)
    {
        siz = arr.size() - 1;
        tree.resize(siz * 4 + 10);
        left = 0, right = siz;
        buildTree(0, siz, 0, arr);
    }

    void buildTree(int l, int r, int index, vector<int> &arr)
    {
        if (l == r)
        {
            tree[index] = arr[l];
            return;
        }
        int mid = (l + r) / 2;

        buildTree(l, mid, 2 * index + 1, arr);
        buildTree(mid + 1, r, 2 * index + 2, arr);
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
    }

    void updateHelper(int pos, int val, int l, int r, int index)
    {
        if (r == l)
        {
            tree[index] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos >= l and pos <= mid)
            updateHelper(pos, val, l, mid, 2 * index + 1);
        else
            updateHelper(pos, val, mid + 1, r, 2 * index + 2);
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
    }

    void update(int pos, int val)
    {
        updateHelper(pos, val, 0, right, 0);
    }

    long long queryHelper(int l, int r, int index, int le, int re)
    {
        if (l <= le and r >= re)
            return tree[index];
        if (l > re or r < le)
            return 0;
        int mid = (le + re) / 2;
        return queryHelper(l, r,  2 * index + 2, mid + 1, re) + queryHelper(l, r, 2 * index + 1, le, mid);
    }

    long long query(int l, int r)
    {
        return queryHelper(l, r, 0, 0, siz);
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n;
    cin >> n;
    vector<int> arr(2 * n), empty(2 * n, 0);
    for (auto &i : arr)
    {
        cin >> i;
    }
    segmentTree tree(empty);
    map<int, int> m;
    vector<long long> ans(n + 1, 0);
    for (int i = 0; i < 2 * n; i++)
    {
        if (m[arr[i]] == 0)
        {
            m[arr[i]] = i + 1;
            tree.update(i, 1);
        }
        else
        {
            ans[arr[i]] = tree.query(m[arr[i]] - 1, i) - 1;
            tree.update(m[arr[i]] - 1, -1);
            tree.update(i, 1);
        }
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}