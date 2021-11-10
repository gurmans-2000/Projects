/*
 -------------------------------------
 File:    bst.c
 Project: final_questions
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-12
 -------------------------------------
 */
#include<stdio.h>
#include<stdlib.h>
#ifndef NULL
#define NULL   ((void *) 0)
#endif

struct node {
	int key;
	struct node *left, *right;
};

struct node* BST_Search(struct node *root, int data) {
	while (root) {
		if (data == root->key) {
			return root;
		} else if (data < root->key)
			root = root->left;
		else
			root = root->right;
	}
}

struct node* recursive_search(struct node *root, int data) {
	if (root == NULL)
		return NULL;
	else if (data = root->key)
		return root;
	else if (data < root->key)
		return recurisve_search(root->left, data);
	else
		return recursive_search(root->right, data);
}

struct node* newNode(int item1) {
	struct node *temp1 = (struct node*) malloc(sizeof(struct node));
	temp1->key = item1;
	temp1->left = temp1->right = NULL;
	return temp1;
}

void inorder(struct node *root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d \n", root->key);
		inorder(root->right);
	}

}

struct node* insert(struct node *node, int key) {
	if (node == NULL)
		return newNode(key);
	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	return node;
}

struct node* minValueNode(struct node *node) {
	struct node *current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

struct node* deleteNode(struct node *root, int key) {
	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else {
		if (root->left == NULL) {
			struct node *temp1 = root->right;
			free(root);
			return temp1;
		} else if (root->right == NULL) {
			struct node *temp1 = root->left;
			free(root);
			return temp1;
		}
		struct node *temp1 = minValueNode(root->right);
		root->key = temp1->key;
		root->right = deleteNode(root->right, temp1->key);
	}
	return root;
}
