#pragma once
#include<iostream>
#include<vector>
using namespace std;
template<typename Comparable>
class BTree {
public:
	BTree(int &ord,Comparable none=0):root(nullptr),leaf(nullptr),t(ord),None(none){}
	BTree(const B_Tree_Plus& org) {
		root = clone(org.root);
	}
	~BTree() {
		makeEmpty();
	}

private:
	const int t;
	Comparable None;
	struct Node {
		bool isleaf;
		vector <Comparable > key;
		int	n;
		vector<Node* > ptr;
		Node(int num_of_key) :n(num_of_key), isleaf(false) {
			key = vector<Comparable >(num_of_key, 0);
			ptr = vector<Node* >(num_of_key + 1, nullptr);
		}
		Node() {
			key = vector<Comparable >(2 * t - 1, None);
			ptr = vector<Node* >(2 * t, nullptr);
			n = 0;
			isleaf = false;
		}
		Node(Node* &x, int begin, int end) {
			key = vector<Comparable >(2 * t - 1, None);
			ptr = vector<Node* >(2 * t, nullptr);
			n = end - begin + 1;
			for (int i = 0; i < n; i++) {
				key[i] = x->key[i+begin];
				ptr[i] = x->ptr[i + begin];
			}
			isleaf = x->isleaf;
		}
	 };
	Node* root,leaf;
	Node* search(Comparable& elm, Node* &nd,int &pos);
	void insert(Comparable& elm, Node* &nd);
	void remove(Comparable& elm, Node* &nd);
	void insert_nonfull(Comparable& elm, Node*& nd);
	void split(int i, Node*& nd) {
		Node* old = nd->ptr[i];
		y = new Node(nd->ptr[i], 0, t - 2);
		z =new Node(nd->ptr[i],t,2*t-2);
		for (int j = n - 1; j >= i+1; j--) {
			nd->key[j + 1] = nd->key[j];
			nd->key[i] = nd->ptr[i]->key[t - 1];
		}
		for (int j = n; j >= i+2; j--) {
			nd->ptr[j + 1] = nd->ptr[j];
		}
		nd->ptr[i] = y;
		nd->ptr[i + 1] = z;
		//nd->key.insert(nd->key.begin() + i, nd->ptr[i]->key[t - 1]);
		//nd->ptr.insert(nd->ptr.begin() + i + 1, z);
		delete old;
		old = nullptr;
		nd->n++;
	}
public:
	void search(Comparable &elm)const;
	void insert(Comparable &elm);
	void remove(Comparable &elm);
	void display(Node* nd);
	void cleanUp(Node* nd);

};
template<typename Comparable>
typename BTree<Comparable>::Node* search(Comparable& elm, typename BTree<Comparable>::Node* &nd,int &pos) {
	int i = 0;
	while (i < nd->n && elm > nd->key[i])i++;
	if (i < -nd->n && elm == nd->key[i]) {
		pos = i;
		return nd;
	}
	else if (nd->isleaf) {
		pos = -1;
		return nullptr;
	}
	else {
		return search(elm, nd->ptr[i]);
	}
}
template <typename Comparable>
void insert(Comparable& elm, typename BTree<Comparable>::Node*& nd) {
	Node* r = nd;
	if (r->n == 2 * t - 1) {
		Node* s = new Node();
		nd = s;
		s->ptr[0] = r;
		split(0, s);
		insert_nonfull(elm, s);
	}
	else insert_nonfull(elm, s);
}
template <typename Comparable>
void insert_nonfull(Comparable& elm, typename BTree<Comparable>::Node*& nd) {
	int i = nd->n-1;
	if (nd->isleaf) {
		while (i >= 0 && elm > nd->key[i]) {
			nd->key[i+1] = nd->key[i];
			i--;
		}
		nd->key[i + 1] = elm;
		nd->n++;
	}
	else {
		while (i >= 0 && elm > nd->key[i])i--;
		i++;
		if (nd->ptr[i]->n == 2 * t - 1) {
			split(i,nd);
			if (elm < nd->key[i])i++;
		}
		insert_nonfull(elm, nd->ptr[i]);
	}
}
template<typename Comparable>
void typename BTree<Comparable>::remove(Comparable& elm, typename BTree<Comparable>::Node*& nd) {
	int i = nd->n - 1;
	while (i >= 0 && nd->key[i] >=elm) {
		i--;
	}
	i++;
	if (nd->key[i] == elm) {
		if (nd->isleaf) {
			for (int j = n - 2; j >= i; j--) {
				nd->key[j] = nd->key[j + 1];
			}
			nd->key[n - 1] = None;
			nd->n--;
		}
		else {
			if(nd->ptr[i]->n>=t){}
			else if(nd->ptr[i]->n>=t){}
			else {}
		}
	}
}