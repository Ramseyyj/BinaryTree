#pragma once
#pragma warning( disable : 4018 )

#include <iostream>
#include <queue>
#include <string>
using namespace std;


template <typename E>
class BTNode
{
public:
	BTNode* parent;
	BTNode* left;
	BTNode* right;
	E data;

	// methods for building tree
	BTNode() { parent = left = right = NULL; }
	BTNode(const E& d) { data = d; parent = left = right = NULL; }

	BTNode* addLeft(BTNode* n) { left = n;  n->parent = this; return n; }
	BTNode* addLeft(const E& d) { return addLeft(new BTNode(d)); }
	BTNode* addRight(BTNode* n) { right = n; n->parent = this;  return n; }
	BTNode* addRight(const E& d) { return addRight(new BTNode(d)); }

	// methods for traverse
	virtual void visitNode() { cout << data << " "; }
	virtual void visitPreOrder() {

		visitNode();

		if (hasLeft())
		{
			left->visitPreOrder();
		}

		if (hasRight())
		{
			right->visitPreOrder();
		}
	}
	virtual void visitPostOrder() {

		if (hasLeft())
		{
			left->visitPostOrder();
		}
		
		if (hasRight())
		{
			right->visitPostOrder();
		}

		visitNode();
	}
	virtual void visitInOrder() {

		if (hasLeft())
		{
			left->visitInOrder();			
		}

		visitNode();

		if (hasRight())
		{
			right->visitInOrder();
		}
	}
	virtual void visitLevelOrder() {

		queue<BTNode*> Q;

		Q.push(this);

		while (!Q.empty())
		{
			BTNode* now = Q.front();
			Q.pop();
			now->visitNode();

			if (now->hasLeft())
			{
				Q.push(now->left);
			}

			if (now->hasRight())
			{
				Q.push(now->right);
			}
		}
	}

	// methods for properties
	bool isRoot() { return parent == NULL; }
	bool hasLeft() { return left != NULL; }
	bool hasRight() { return right != NULL; }
	bool hasBoth() { return hasLeft() && hasRight(); }
	bool isLeaf() { return !hasLeft() && !hasRight(); }
	int getSize() {

		int n = 1;

		if (hasLeft()) n += left->getSize();
		if (hasRight()) n += right->getSize();

		return n;
	}
	int getLeftBranchHeight() { // returns the height of left branch

		if (hasLeft())
		{
			return left->getHeight() + 1;
		}
		else
		{
			return 0;
		}

	}
	int getRightBranchHeight() { // returns the height of right branch

		if (hasRight())
		{
			return right->getHeight() + 1;
		}
		else
		{
			return 0;
		}
	}
	int getHeight() {

		int leftHeight = getLeftBranchHeight();
		int rightHeight = getRightBranchHeight();

		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}
	int getDepth() {

		if (isRoot())
		{
			return 0;
		}
		else
		{
			return parent->getDepth() + 1;
		}
	}

	// methods to find some node
	BTNode* getRoot() {
		if (isRoot()) return this;
		return parent->getRoot();
	}
	BTNode* findInFirst() {  // first node in in-order
		
		if (hasLeft())
		{
			return left->findInFirst();
		}
		else
		{
			return this;
		}
	}
	BTNode* findLeftMost() { return findInFirst(); }
	BTNode* findInLast() {  // last node in in-order
		
		if (hasRight())
		{
			return right->findInLast();
		}
		else
		{
			return this;
		}
	}
	BTNode* findRightMost() { return findInLast(); }
	BTNode* findPostFirst() {  // first node in post-order
		
		if (hasLeft())
		{
			return left->findPostFirst();
		}
		else if (hasRight())
		{
			return right->findPostFirst();
		}
		else
		{
			return this;
		}
	}

	//-- ex C-7.5
	// from : child from which this was called recursively
	BTNode* findPreNext() { // next node after this in pre-order
							
		if (isLeaf())
		{
			if (this->isRoot())
			{
				return NULL;
			}

			BTNode* now = parent;
			BTNode* front = this;

			while ( (!now->hasRight()) || (now->right == front) )
			{
				if (now->isRoot())
				{
					return NULL;
				}

				front = now;
				now = now->parent;
			}

			if (now->hasRight())
			{
				return now->right;
			}
			else
			{
				return NULL;
			}
		
		}
		else if (hasLeft())
		{
			return left;
		}
		else
		{
			return right;
		}		
	}

	// from : child from which this was called recursively
	BTNode* findInNext() { // next node after this in in-order
		
		if (hasRight())
		{
			return right->findInFirst();
		}
		else
		{
			BTNode* now = this;

			while ( (!now->isRoot()) && (now->parent->right == now) )
			{
				now = now->parent;
			}

			if (now->isRoot())
			{
				return NULL;
			}
			else
			{
				return now->parent;
			}
		}
	}

	BTNode* findPostNext() {  // next node after this in post-order
		
		if (isRoot())
		{
			return NULL;
		}

		BTNode* p = this->parent;

		if ((this == p->left) && (p->hasRight()))
		{
			return p->right->findPostFirst();
		}
		else
		{
			return p;
		}
	}

	// Lowest Common Ancestor : ex C.7-24
	BTNode* findLCA(BTNode* that) {
		
		BTNode* node1 = this;
		BTNode*	node2 = that;

		int len1 = node1->getDepth();
		int len2 = node2->getDepth();

		for (; len1 > len2; len1--)
		{
			node1 = node1->parent;
		}
		for (; len2 > len2; len2--)
		{
			node2 = node2->parent;
		}

		while (node1 && node2 && node1 !=node2)		
		{
			node1 = node1->parent;
			node2 = node2->parent;
		}

		if (node1 == node2)
		{
			return node1;
		}
		else
		{
			return NULL;
		}
	}
	static BTNode* findLCA(BTNode* v, BTNode* w) {
		return v->findLCA(w);
	}

	// diameter of a subtree : ex C.7-25
	int getDiameter() {
		
		int max = 0;
		int leftDiameter = 0;
		int rightDiameter = 0;

		if (hasLeft())
		{
			leftDiameter = left->getDiameter();
			max += left->getHeight() + 1;
		}

		if (hasRight())
		{
			rightDiameter = right->getDiameter();
			max += right->getHeight() + 1;

		}		

		if (leftDiameter > max)
		{
			max = leftDiameter;
		}
		if (rightDiameter > max)
		{
			max = rightDiameter;
		}

		return max;
	}

	// ex C-7.11
	int getBalanceFactor() {
		
		return abs(getLeftBranchHeight() - getRightBranchHeight());
	}

	virtual ~BTNode() {
		if (hasLeft()) delete left;
		if (hasRight()) delete right;
	}
};
