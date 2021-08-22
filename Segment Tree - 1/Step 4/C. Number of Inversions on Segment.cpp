#include <bits/stdc++.h>
using namespace std;

class node {
public:
    int cnt[41];
    long long inver;
    node()
    {
        inver = 0;
        for (int i = 0; i <= 40; i++) {
            cnt[i] = 0;
        }
    }
};

node merge(node a, node b)
{
    node res;
    for (int i = 1; i <= 40; i++)
    {
        for (int j = i + 1; j <= 40; j++)
        {
            res.inver += 1LL * b.cnt[i] * a.cnt[j];
        }
        res.cnt[i] = a.cnt[i] + b.cnt[i];
    }
    res.inver += a.inver + b.inver;
    return res;
}

class segmentTree {
    vector<node> tree;
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
            tree[index].inver = 0;
            tree[index].cnt[arr[l]] = 1;
            return;
        }
        int mid = (l + r) / 2;

        buildTree(l, mid, 2 * index + 1, arr);
        buildTree(mid + 1, r, 2 * index + 2, arr);
        tree[index] = merge(tree[2 * index + 1], tree[2 * index + 2]);
    }

    void updateHelper(int pos, int val, int l, int r, int index)
    {
        if (r == l)
        {
            node temp;
            temp.cnt[val] = 1;
            tree[index] = temp;
            return;
        }
        int mid = (l + r) / 2;
        if (pos >= l and pos <= mid)
            updateHelper(pos, val, l, mid, 2 * index + 1);
        else
            updateHelper(pos, val, mid + 1, r, 2 * index + 2);
        tree[index] = merge(tree[2 * index + 1], tree[2 * index + 2]);
    }

    void update(int pos, int val)
    {
        updateHelper(pos, val, 0, right, 0);
    }

    node queryHelper(int l, int r, int index, int le, int re)
    {
        if (l <= le and r >= re)
            return tree[index];
        if (l > re or r < le)
            return node();
        int mid = (le + re) / 2;
        return merge(queryHelper(l, r,  2 * index + 1, le, mid), queryHelper(l, r, 2 * index + 2, mid + 1, re));
    }

    node query(int l, int r)
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
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            cout << tree.query(l, r).inver << endl;
        }
        else
        {
            int pos, val;
            cin >> pos >> val;
            pos--;
            tree.update(pos, val);
        }
    }
}