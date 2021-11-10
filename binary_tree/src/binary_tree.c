/*
 -------------------------------------
 File:    binary_tree.c
 Project: final_questions
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-12
 -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

NODE* add(int item) {
	NODE *temp = (NODE*) malloc(sizeof(NODE));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

void preOrder(NODE *root) {
	if (root == NULL)
		return;
	printf("%d ", root->data);
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(NODE *root) {
	if (root == NULL)
		return;
	inOrder(root->left);
	printf("%d ", root->data);
	inOrder(root->right);
}

void breadthFirst(NODE *root, int k) {
	if (!root)
		return;
	if (k == 1)
		printf("%d ", root->data);
	else if (k > 1) {
		breadthFirst(root->left, k - 1);
		breadthFirst(root->right, k - 1);
	}
}

void depthFirst(NODE *root) {
	if (root == NULL)
		return;
	if (root->left)
		depthFirst(root->left);
	if (root->right)
		depthFirst(root->right);
	printf("%d ", root->data);
}

void postOrder(NODE *root) {
	if (root == NULL)
		return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->data);
}

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

int height(NODE *root) {
	if (root == NULL)
		return 0;
	return max(height(root->left), height(root->right)) + 1;
}

int numNodes(NODE *root) {
	if (root == NULL)
		return 0;
	return (numNodes(root->left) + 1 + numNodes(root->right));
}

int numLeaves(NODE *root) {
	if (root == NULL)
		return 0;
	if (!root->left && !root->right)
		return 1;
	return (numLeaves(root->left) + numLeaves(root->right));
}

typedef struct treeinfo {
	int height;
	int leaf_count;
} TREEINFO;

TREEINFO treeinfo(NODE *root) {
	TREEINFO r = { 0 };
	if (root != NULL) {
		if (root->left == NULL && root->right == NULL) {
			r.height = 1;
			r.leaf_count = 1;

		} else {
			TREEINFO
			ls = (root->left)? treeinfo(root->left); {
				0
			};
			TREEINFO
			ls = (root->right)? treeinfo(root->right); {
				0
			};
			r.height = 1 + (ls.height >= rs.height) ? ls.height : rs.height;
			r.leaf_count = ls.leaf_count + rs.leaf_count;
		}
	}
	return r;
}

int main() {
	NODE *root = add(1);
	root->left = add(2);
	root->right = add(3);
	root->left->left = add(4);
	root->left->right = add(5);
	printf("PREORDER : ");
	preOrder(root); //printing the Tree
	printf("\nINORDER : ");
	inOrder(root);
	printf("\nPOSTORDER : ");
	postOrder(root);
	printf("\nBREADTH FIRST : ");
	for (int i = 1; i <= height(root); i++)
		breadthFirst(root, i);
	printf("\nDEPTH FIRST : ");
	depthFirst(root);
	printf("\nNumber of nodes : %d\n", numNodes(root));
	printf("\nHeight : %d\n", height(root));
	printf("\nNumber of leaves : %d\n", numLeaves(root));
	return 0;
}

