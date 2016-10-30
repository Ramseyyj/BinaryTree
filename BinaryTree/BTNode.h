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

		this->visitNode();

		if (this->hasBoth())
		{
			left->visitPreOrder();
			right->visitPreOrder();
		}
		else if (this->hasLeft())
		{
			left->visitPreOrder();
		}
		else if (this->hasRight())
		{
			right->visitPreOrder();
		}
	}
	virtual void visitPostOrder() {

		if (this->hasBoth())
		{
			left->visitPostOrder();
			right->visitPostOrder();
		}
		else if (this->hasLeft())
		{
			left->visitPostOrder();
		}
		else if (this->hasRight())
		{
			right->visitPostOrder();
		}

		this->visitNode();
	}
	virtual void visitInOrder() {

		if (this->hasBoth())
		{
			left->visitInOrder();
			this->visitNode();
			right->visitInOrder();
		}
		else if (this->hasLeft())
		{
			left->visitInOrder();
			this->visitNode();
		}
		else if (this->hasRight())
		{
			this->visitNode();
			right->visitInOrder();
		}
		else
		{
			this->visitNode();
		}

	}
	virtual void visitLevelOrder() {

		queue<BTNode*> q1;
		BTNode* now;

		q1.push(this);

		while (!q1.empty())
		{
			now = q1.front();
			q1.pop();
			now->visitNode();

			if (now->hasBoth())
			{
				q1.push(now->left);
				q1.push(now->right);
			}
			else if (now->hasLeft())
			{
				q1.push(now->left);
			}
			else if (now->hasRight())
			{
				q1.push(now->right);
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

		if (this->isLeaf())
		{
			return 1;
		}
		else if (this->hasBoth())
		{
			return left->getSize() + right->getSize() + 1;
		}
		else if (this->hasLeft())
		{
			return left->getSize() + 1;
		}
		else if (this->hasRight())
		{
			return right->getSize() + 1;
		}
		else
		{
			return 0;
		}
	}
	int getLeftBranchHeight() { // returns the height of left branch

		if (this->hasLeft())
		{
			return left->getHeight() + 1;
		}
		else
		{
			return 0;
		}

	}
	int getRightBranchHeight() { // returns the height of right branch

		if (this->hasRight())
		{
			return right->getHeight() + 1;
		}
		else
		{
			return 0;
		}
	}
	int getHeight() {

		int leftHeight = this->getLeftBranchHeight();
		int rightHeight = this->getRightBranchHeight();

		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}
	int getDepth() {

		if (this->isRoot())
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
							 //... fill this method
		return NULL;
	}
	BTNode* findLeftMost() { return findInFirst(); }
	BTNode* findInLast() {  // last node in in-order
							//... fill this method
		return NULL;
	}
	BTNode* findRightMost() { return findInLast(); }
	BTNode* findPostFirst() {  // first node in post-order
							   //... fill this method
		return NULL;
	}

	//-- ex C-7.5
	// from : child from which this was called recursively
	BTNode* findPreNext() { // next node after this in pre-order
							//... fill this method
		return NULL;
	}

	// from : child from which this was called recursively
	BTNode* findInNext() { // next node after this in in-order
						   //... fill this method
		return NULL;
	}

	BTNode* findPostNext() {  // next node after this in post-order
							  //... fill this method
		return NULL;
	}

	// Lowest Common Ancestor : ex C.7-24
	BTNode* findLCA(BTNode* that) {
		//... fill this method
		return NULL;
	}
	static BTNode* findLCA(BTNode* v, BTNode* w) {
		return v->findLCA(w);
	}

	// diameter of a subtree : ex C.7-25
	int getDiameter() {
		//... fill this method
		return 0;
	}

	// ex C-7.11
	int getBalanceFactor() {
		//... fill this method
		return 0;
	}

	virtual ~BTNode() {
		if (hasLeft()) delete left;
		if (hasRight()) delete right;
	}
};
