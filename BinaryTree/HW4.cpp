// HW4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BTNode.h"


typedef BTNode<string>* BTNodePtr;

BTNodePtr buildTestTree7 () {
	BTNodePtr L = new BTNode<string>("L");
	BTNodePtr E = L->addLeft ("E");
	BTNodePtr N = L->addRight ("N");
	BTNodePtr B = E->addLeft ("B");
	BTNodePtr H = E->addRight ("H");
	BTNodePtr R = N->addRight ("R");
	BTNodePtr P = R->addLeft ("P");
    return L;
}

BTNodePtr buildTestTree26 () {
	BTNodePtr A = new BTNode<string>("A");
	BTNodePtr B = A->addLeft ("B");
	BTNodePtr C = A->addRight ("C");
	BTNodePtr D = B->addLeft ("D");
	BTNodePtr E = B->addRight ("E");
	BTNodePtr F = C->addRight ("F");
	BTNodePtr G = D->addLeft ("G");
	BTNodePtr H = E->addRight ("H");
	BTNodePtr I = F->addRight ("I");
	BTNodePtr J = G->addRight ("J");
	BTNodePtr K = H->addLeft ("K");
	BTNodePtr L = I->addLeft ("L");
	BTNodePtr M = I->addRight ("M");
	BTNodePtr N = J->addLeft ("N");
	BTNodePtr O = K->addRight ("O");
	BTNodePtr P = L->addRight ("P");
	BTNodePtr Q = N->addLeft ("Q");
	BTNodePtr R = N->addRight ("R");
	BTNodePtr S = O->addLeft ("S");
	BTNodePtr T = O->addRight ("T");
	BTNodePtr U = Q->addLeft ("U");
	BTNodePtr V = Q->addRight ("V");
	BTNodePtr W = T->addLeft ("W");
	BTNodePtr X = V->addRight ("X");
	BTNodePtr Y = W->addLeft ("Y");
	BTNodePtr Z = Y->addLeft ("Z");
    return A;
}


void testSizeHeightETC (BTNodePtr root) {
    cout << "Properites of the tree rooted at " << root->data << endl;
	cout << "Size = " << root->getSize() << endl;
	cout << "Height = " << root->getHeight() << endl;
	cout << "Diameter = " << root->getDiameter() << endl;
	cout << "Balance factor = " << root->getBalanceFactor() << endl;
	BTNodePtr leftMost = root->findInFirst();
	if (! leftMost) return;
	BTNodePtr rightMost = root->findInLast();
	if (! rightMost) return;
	BTNodePtr lca = leftMost->findLCA (rightMost);
	if (! lca) return;
	cout << "LCA between " << leftMost->data << " and " << rightMost->data << " is ";
	cout << lca->data << endl;
}

void testPreOrder (BTNodePtr root) {
    cout << "Pre-Order Traverse Test\n";
    root->visitPreOrder();    cout << endl;
    BTNodePtr s = root;  
    while (s != NULL) {
		s->visitNode();  
		s = s->findPreNext();
	}
    cout << endl;
}

void testInOrder (BTNodePtr root) {
    cout << "In-Order Traverse Test\n";
    root->visitInOrder();    cout << endl;
	BTNodePtr s = root->findInFirst();  
    while (s != NULL) {
		s->visitNode();  
		s = s->findInNext();
	}
    cout << endl;
}

void testPostOrder (BTNodePtr root) {
    cout << "Post-Order Traverse Test\n";
    root->visitPostOrder();    cout << endl;
	BTNodePtr s = root->findPostFirst();  
    while (s != NULL) {
		s->visitNode();  
		s = s->findPostNext();
	}
    cout << endl;
}

void testLevelOrder (BTNodePtr root) {
    cout << "Level-Order Traverse Test\n";
    root->visitLevelOrder();    cout << endl;
}


void testBinaryTree(BTNodePtr root)
{
	testSizeHeightETC (root);
	testSizeHeightETC (root->left);
	testSizeHeightETC (root->right);
	testPreOrder (root);
	testInOrder (root);
	testPostOrder (root);
	testLevelOrder (root);
}


void main()
{
	cout << "-----------------------------------------------\n";
	BTNodePtr T7 = buildTestTree7();
	testBinaryTree (T7);
	delete T7;
	cout << "-----------------------------------------------\n";
	BTNodePtr T26 = buildTestTree26();
	testBinaryTree (T26);
	delete T26;
}

