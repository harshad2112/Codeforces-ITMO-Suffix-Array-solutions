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
        {
            return tree[index];
        }
        if (l > re or r < le)
            return 0;
        int mid = (le + re) / 2;
        return queryHelper(l, r, 2 * index + 1, le, mid) + queryHelper(l, r, 2 * index + 2, mid + 1, re);
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
    int n, q;
    cin >> n;
    vector<int> arr(n), arr2(n);
    for (auto &i : arr)
    {
        cin >> i;
    }
    for (int i = 0; i < n; i++)
    {
        if (i % 2)
        {
            arr2[i] = arr[i];
            arr[i] = -arr[i];
        }
        else
        {
            arr2[i] = -arr[i];
        }
    }
    segmentTree tree(arr);
    segmentTree tree2(arr2);
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 0)
        {
            int pos, val;
            cin >> pos >> val;
            pos--;
            if (pos % 2)
            {
                tree2.update(pos, val);
                tree.update(pos, -val);
            }
            else
            {
                tree2.update(pos, -val);
                tree.update(pos, val);
            }
        }
        else
        {
            int l, r;
            cin >> l >> r;
            l--, r--;
            if (l % 2)
            {
                cout << tree2.query(l, r) << endl;
            }
            else
            {
                cout << tree.query(l, r) << endl;
            }
        }
    }
}