#include <bits/stdc++.h>
using namespace std;

class segmentTree {
    vector<int> tree;
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
        for (int i = 0; i < 4 * arr.size(); i++)
            tree[i] = INT_MAX;
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
        tree[index] = min(tree[2 * index + 1], tree[2 * index + 2]);
    }

    void update(int pos, int val)
    {
        updateHelper(pos, val, 0, right, 0);
    }

    int queryHelper(int l, int r, int val, int index, int le, int re)
    {
        if (l > r)
            return 0;
        if (le == re)
        {
            int res = tree[index] <= val;
            tree[index] = INT_MAX;
            update(le, INT_MAX);
            return res;
        }
        int mid = (le + re) / 2;
        int res = 0;
        if (tree[2 * index + 1] <= val)
            res = queryHelper(l, min(r, mid), val, 2 * index + 1, le, mid);
        if (tree[2 * index + 2] <= val)
            res += queryHelper(max(l, mid + 1), r, val, 2 * index + 2, mid + 1, re);
        return res;
    }

    int query(int l, int r, int val)
    {
        return queryHelper(l, r, val, 0, 0, siz);
    }
};

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> MAX(n, 0);
    segmentTree tree(MAX);
    for (int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        if (t == 2)
        {
            int l, r, val;
            cin >> l >> r >> val;
            r--;
            cout << tree.query(l, r, val) << "\n";
        }
        else
        {
            int pos, val;
            cin >> pos >> val;
            tree.update(pos, val);
        }
    }
}