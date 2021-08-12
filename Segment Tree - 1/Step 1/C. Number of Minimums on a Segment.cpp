#include <bits/stdc++.h>
using namespace std;

class segmentTree {
    vector<pair<long long, int>> tree;
    int left, right, siz;
public:
    segmentTree(vector<int> &arr)
    {
        siz = arr.size();
        tree.resize(siz * 4 + 10);
        left = 0, right = siz;
        buildTree(0, siz, 0, arr);
    }

    void buildTree(int l, int r, int index, vector<int> &arr)
    {
        if (l == r)
        {
            tree[index] = {arr[l], 1};
            return;
        }
        int mid = (l + r) / 2;

        buildTree(l, mid, 2 * index + 1, arr);
        buildTree(mid + 1, r, 2 * index + 2, arr);
        if (tree[2 * index + 1].first == tree[2 * index + 2].first)
        {
            tree[index] = {tree[2 * index + 1].first, tree[2 * index + 1].second + tree[2 * index + 2].second};
        }
        else if (tree[2 * index + 1].first > tree[2 * index + 2].first)
        {
            tree[index] = tree[2 * index + 2];
        }
        else
            tree[index] = tree[2 * index + 1];
    }

    void updateHelper(int pos, int val, int l, int r, int index)
    {
        if (r == l)
        {
            tree[index] = {val, 1};
            return;
        }
        int mid = (l + r) / 2;
        if (pos >= l and pos <= mid)
            updateHelper(pos, val, l, mid, 2 * index + 1);
        else
            updateHelper(pos, val, mid + 1, r, 2 * index + 2);
        if (tree[2 * index + 1].first == tree[2 * index + 2].first)
        {
            tree[index] = {tree[2 * index + 1].first, tree[2 * index + 1].second + tree[2 * index + 2].second};
        }
        else if (tree[2 * index + 1].first > tree[2 * index + 2].first)
        {
            tree[index] = tree[2 * index + 2];
        }
        else
            tree[index] = tree[2 * index + 1];
    }

    void update(int pos, int val)
    {
        updateHelper(pos, val, 0, right, 0);
    }

    pair<int, int> queryHelper(int l, int r, int index, int le, int re)
    {
        if (l <= le and r >= re) {
            return tree[index];
        }
        if (l > re or r < le or l>r)
        {
            return {INT_MAX, 0};
        }
        int mid = (le + re) / 2;
        pair<int, int> lv, rv;
        lv = queryHelper(l, r, 2 * index + 1, le, mid);
        rv = queryHelper(l, r, 2 * index + 2, mid + 1, re);
        if (lv.first == rv.first and lv.first != INT_MAX)
        {
            return {lv.first, lv.second + rv.second};
        }
        else
            return min(lv, rv);

    }

    pair<int, int> query(int l, int r)
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
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (auto &i : arr)
    {
        cin >> i;
    }
    segmentTree tree(arr);
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int i, v;
            cin >> i >> v;
            tree.update(i, v);
        }
        if (t == 2)
        {
            int l, r;
            cin >> l >> r;
            r--;
            pair<int, int> ans = tree.query(l, r);
            cout << ans.first << " " << ans.second;
            cout << endl;
        }
    }
}