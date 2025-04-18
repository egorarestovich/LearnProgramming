﻿#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

vector<int64_t> values = { 1, 2, 3, 4, 5 }; // my test values, used in Segment_Tree, 
// if you want to rename this array, rename also in Segment_Tree to work

class Fenwick_Tree
{
public:
	vector<int64_t> tree;
	int size = 0;
	Fenwick_Tree(int size)
	{
		this->size = size;
		tree.resize(size);
	}
	int64_t sum(int x)
	{
		int64_t result = 0;
		for (; x >= 0; x = (x & (x + 1)) - 1)
		{
			result += tree[x];
		}
		return result;
	}
	int64_t get_sum(int l, int r)
	{
		if (l)
		{
			return sum(r) - sum(l - 1);
		}
		else
		{
			return sum(r);
		}
	}
	void update(int idx, int64_t val)
	{
		for (; idx < size; idx |= idx + 1)
		{
			tree[idx] += val;
		}
	}
};
class Segment_Tree
{
public:
	vector<int64_t> tree;
	int size = 0;
	Segment_Tree(int size)
	{
		this->size = size;
		tree.resize(size * 4);
	}
	void build(int v, int l, int r)
	{
		if (l == r)
		{
			tree[v] = values[l];
			return;
		}
		int mid = (l + r) / 2;
		build(v * 2, l, mid);
		build(v * 2 + 1, mid + 1, r);
		tree[v] = tree[v * 2] + tree[v * 2 + 1];
	}
	void build()
	{
		build(1, 0, size - 1);
	}
	int64_t get_sum(int v, int tl, int tr, int l, int r)
	{
		if (tl >= l && tr <= r)
		{
			return tree[v];
		}
		if (tl > r || tr < l)
		{
			return 0;
		}
		int mid = (l + r) / 2;
		return get_sum(v * 2, l, mid, l, r) + get_sum(v * 2 + 1, mid + 1, r, l, r);
	}
	int64_t get_sum(int l, int r)
	{
		return get_sum(1, 0, size - 1, l, r);
	}
};
class Dekart_Tree
{
	static std::minstd_rand gen;
	struct Node
	{
		int64_t val, priority;
		Node* l = nullptr, * r = nullptr;
		Node(int64_t val) : val(val), priority(gen()) {};
	} *root = nullptr;
	static Node* merge(Node* a, Node* b)
	{
		if (!a || !b)
		{
			return a ? a : b;
		}
		if (a->priority > b->priority)
		{
			a->r = merge(a->r, b);
			return a;
		}
		else
		{
			b->l = merge(a, b->l);
			return b;
		}
	}
	static void split(Node* n, int64_t val, Node*& a, Node*& b)
	{
		if (!n)
		{
			a = b = nullptr;
			return;
		}
		if (n->val < val)
		{
			split(n->r, val, n->r, b);
			a = n;
		}
		else
		{
			split(n->l, val, a, n->l);
			b = n;
		}
	}
public:
	void insert(int64_t key)
	{
		Node* smaller, * greater;
		split(root, key, smaller, greater);
		root = merge(merge(smaller, new Node(key)), greater);
	}
	void erase(int64_t key)
	{
		Node* smaller,* equal, * greater;
		split(root, key, smaller, greater);
		split(greater, key + 1, equal, greater);
		root = merge(smaller, greater);
	}
	bool is_contains(int64_t key)
	{
		Node* smaller, * equal, * greater;
		split(root, key, smaller, greater);
		split(greater, key + 1, equal, greater);
		bool res = equal;
		root = merge(merge(smaller, equal), greater);
		return res;
	}
};
std::minstd_rand Dekart_Tree::gen;

int main()
{
	// write your test code here.
}   