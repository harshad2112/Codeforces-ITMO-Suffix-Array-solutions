#include <bits/stdc++.h>
using namespace std;

class segmentTree {
    vector<long long> tree, lazy;
    int left, right, siz;
public:
    segmentTree(vector<int> &arr)
    {
        siz = arr.size() - 1;
        tree.resize(siz * 4 + 10);
        lazy.resize(siz * 4 + 10);
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
        tree[index] = max(tree[2 * index + 2], tree[2 * index + 1]);

    }

    void updateHelper(int l, int r, int val, int le, int re, int index)
    {
        if (lazy[index] != 0)
        {
            tree[index] += (re - le + 1) * lazy[index];
            if (le != re)
            {
                lazy[2 * index + 1] += lazy[index];
                lazy[2 * index + 2] += lazy[index];
            }
            lazy[index] = 0;
        }
        if (l <= le and r >= re)
        {
            if (le != re)
            {
                lazy[2 * index + 1] += val;
                lazy[2 * index + 2] += val;
            }
            tree[index] += (re - le + 1) * val;
            return;
        }
        if (l > re or r < le)
            return;
        int mid = (le + re) / 2;
        updateHelper(l, r, val, le, mid, 2 * index + 1);
        updateHelper(l, r, val, mid + 1, re, 2 * index + 2);
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];

    }

    void update(int l, int r, int val)
    {
        updateHelper(l, r, val, 0, right, 0);
    }

    long long queryHelper(int ind, int index, int le, int re)
    {
        if (lazy[index] != 0)
        {
            if (le != re)
            {
                lazy[2 * index + 1] += lazy[index];
                lazy[2 * index + 2] += lazy[index];
            }
            tree[index] += lazy[index] * (re - le + 1);
            lazy[index] = 0;
        }
        if (le == re)
        {
            return tree[index];
        }
        int mid = (le + re) / 2;
        if (ind >= le and ind <= mid)
            return queryHelper(ind, 2 * index + 1, le, mid);
        else
            return queryHelper(ind, 2 * index + 2, mid + 1, re);
    }

    long long query(int ind)
    {
        return queryHelper(ind, 0, 0, siz);
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
    vector<int> arr(n, 0);
    segmentTree tree(arr);
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r, val;
            cin >> l >> r >> val;
            r--;
            tree.update(l, r, val);
        }
        else
        {
            int pos;
            cin >> pos;
            cout << tree.query(pos) << endl;
        }
    }
}