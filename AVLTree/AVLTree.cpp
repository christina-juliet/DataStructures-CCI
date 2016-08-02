/*
 * AVLTree.cpp
 *
 *  Created on: May 17, 2016
 *      Author: Christina
 */
#include<iostream>
#include<cstdlib>
using namespace std;
struct node
{
	int data;
	node *left, *right;
	int height;
};
class AVLTree
{
public:
	node* root;

	// constructor
	AVLTree()
	{
		root = NULL;
	}

	// helper functions for insert
	node* createNode(int d)
	{
		node *newNode = new node;
		newNode->data = d;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = 1; // since this is always a leaf node
		return newNode;
	}

	int height(node *n) // This function is needed to handle the condition of n being NULL
	{
		if (n == NULL)
			return 0;
		return n->height;
	}

	node* rightRotate(node *n)
	{
		node *nl = n->left;
		node *nlr = nl->right;
		// perform rotation
		nl->right = n;
		n->left = nlr;
		n->height = max(height(n->left), height(n->right)) + 1;
		nl->height = max(height(nl->left), height(nl->right)) + 1;
		return nl; // returning nl so that n's previous parent gets connected to nl.
	}

	node* leftRotate(node *n)
	{
		node *nr = n->right;
		node *nrl = nr->left;
		// perform rotation
		nr->left = n;
		n->right = nrl;
		n->height = max(height(n->left), height(n->right)) + 1;
		nr->height = max(height(nr->left), height(nr->right)) + 1;
		return nr;
	}

	int getBalanceFactor(node *n)
	{
		if (n == NULL)
			return 0;
		return (height(n->left) - height(n->right));
	}

	node* insert (node *n, int d)
	{
		if (n == NULL)
		{
			return createNode(d);
		}
		if (d < n->data)
		{
			n->left = insert (n->left, d);
		}
		else
		{
			n->right = insert (n->right, d);
		}
		int bf = getBalanceFactor(n);
		// left-left case
		if ((bf > 1) && (d < n->left))
			return rightRotate(n);
		// left-right case
		if ((bf > 1) && (d > n->left))
		{
			n->left = leftRotate(n->left);
			return rightRotate(n);
		}
		// right-right case
		if ((bf < -1) && (d > n->right))
			return leftRotate(n);
		// right-left case
		if ((bf < -1) && (d < n->right))
		{
			n->right = rightRotate(n->right);
			return leftRotate(n);
		}
		// when the tree is balanced already, just return the current node
		return n;
	}

	void insert (int d)
	{
		insert (root, d);
	}
};




