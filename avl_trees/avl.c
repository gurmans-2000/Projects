#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

// A utility functions
int _max(int a, int b)
{
    return (a > b)? a : b;
}

int height(TNODE *np)
{
  int height;

  height = 0;
  if (np) height = np->height;

  return height;
}

int balance_factor(TNODE *np) {
  int bf;
  if (np)
  {
    if (np->left && np->right)
      bf = np->left->height - np->right->height;
    else if (np->left && !np->right)
      bf = np->left->height;
    else if (!np->left && np->right)
      bf = 0 - np->right->height;
    else
      bf = -1;
  }
  return bf;
}

int is_avl(TNODE *root) {
  if (!root)
    return 1;
  if (height(root) < _max(height(root->left), height(root->right)) + 1)
    return 0;
  if (abs(balance_factor(root)) > 1)
    return 0;
  if (root->left && strcmp(root->left->data.name, root->data.name) > 0
    || root->right && strcmp(root->right->data.name, root->data.name) < 0)
    return 0;
  if (!is_avl(root->left) || !is_avl(root->right))
    return 0;
  return 1;
}

TNODE *rotate_right(TNODE *y)
{
  TNODE *temp = y->left;
  TNODE *temp2 = temp->right;

  temp->right = y;
  y->left = temp2;

  y->height = 1 + _max(height(y->left), height(y->right));
  temp->height = 1 + _max(height(temp->left), height(temp->right));

  return temp;
}

TNODE *rotate_left(TNODE *x)
{
  TNODE *temp = x->right;
  TNODE *temp2 = temp->left;

  temp->left = x;
  x->right = temp2;
  
  x->height = 1 + _max(height(x->left), height(x->right));
  temp->height = 1 + _max(height(temp->left), height(temp->right));

  return temp;
}

void insert(TNODE **rootp, char *name, float score)
{
  int bf;

// 1. Perform the normal BST insertion
  if (*rootp == NULL) {
    TNODE *np = (TNODE *) malloc(sizeof(TNODE));
    if (np == NULL) return;
    strcpy(np->data.name, name);
    np->data.score = score;
    np->height = 1;
    np->left = NULL;
    np->right = NULL;
  
    *rootp = np;
    return;
  }
  
  TNODE *root = *rootp;
  if (strcmp(name, root->data.name) < 0 )
    insert(&root->left, name, score);
  else if (strcmp(name, root->data.name) > 0 )
    insert(&root->right, name, score);
  else
    return;

  // 2. update height of this root node
  root->height = 1 + _max(height(root->right), height(root->left));

  // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
  
  bf = balance_factor(root);
  // 4. re-balance if not balanced
      
  // Left-heavy
  if (bf > 1)
  {
    if (balance_factor(root->left) >= 0)
    {
      *rootp = rotate_right(root);
    }else
    {
      root->left = rotate_left(root->left);
      *rootp = rotate_right(root);
    }
  }
  // Right-heavy
  else if (bf < -1)
  {
    if (balance_factor(root->left) <= 0)
    {
      *rootp = rotate_left(root);
    } else
    {
      root->right = rotate_right(root->right);
      *rootp = rotate_left(root);
    }
  }
}

void delete(TNODE **rootp, char *name)
{
  TNODE *root = *rootp;
  TNODE *np;
  int bf;

  if (root == NULL) return;

  if (strcmp(name, root->data.name) == 0) {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      *rootp = NULL;
    } else if (root->left != NULL && root->right == NULL) {
      np = root->left;
      free(root);
      *rootp = np;
    } else if (root->left == NULL && root->right != NULL) {
      np = root->right;
      free(root);
      *rootp = np;
    } else if (root->left != NULL && root->right != NULL) {
      np = extract_smallest_node(&root->right);
      np->left = root->left;
      np->right = root->right;
      free(root);
      *rootp = np;
    }
  } else {
    if (strcmp(name, root->data.name) < 0) {
      delete(&root->left, name);
    } else {
      delete(&root->right, name);
    }
  }

    // If the tree had only one node then return
  if (*rootp == NULL) return;

  root = *rootp;
  
  // 2. update height of this root node
  root->height = 1 + _max(height(root->right), height(root->left));

  // 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
  
  bf = balance_factor(root);
  // 4. re-balance if not balanced
      
  // Left-heavy
  if (bf > 1)
  {
    if (balance_factor(root->left) >= 0)
    {
      *rootp = rotate_right(root);
    }else
    {
      root->left = rotate_left(root->left);
      *rootp = rotate_right(root);
    }
  }
  // Right-heavy
  else if (bf < -1)
  {
    if (balance_factor(root->left) <= 0)
    {
      *rootp = rotate_left(root);
    } else
    {
      root->right = rotate_right(root->right);
      *rootp = rotate_left(root);
    }
  }
}


// following functions are from bst.c of a7
TNODE *extract_smallest_node(TNODE **rootp) {
  TNODE *tnp = *rootp;
  TNODE *parent = NULL;
  if (tnp == NULL) {
    return NULL;
  } else {
    while (tnp->left) {
      parent = tnp;
      tnp = tnp->left;
    }
    if (parent == NULL)
      *rootp = tnp->right;
    else
      parent->left = tnp->right;
    tnp->left = NULL;
    tnp->right = NULL;
    return tnp;
  }
}

TNODE *search(TNODE *root, char *name) {
  TNODE *tp = root;
  while (tp) {
    if (strcmp(name, tp->data.name) == 0) {
       return tp;
    } else if (strcmp(name, tp->data.name) < 0) 
      tp = tp->left;
     else 
      tp = tp->right;
  }    
  return NULL;
}

void clean_tree(TNODE **rootp) {
  if (*rootp) {
    TNODE *np = *rootp;
    if (np->left)
      clean_tree(&np->left);
    if (np->right)
      clean_tree(&np->right);
    free(np);
  }
  *rootp = NULL; ;
}

void display_inorder(TNODE *root) {
  if (root) {
    if (root->left) display_inorder(root->left);
    printf("%-15s%3.1f\n", root->data.name, root->data.score);
    if (root->right) display_inorder(root->right);
  }
}

void display_tree(TNODE *root, int prelen) {
  if (root) {
    int i;
    for (i = 0; i < prelen; i++)
      printf("%c", ' ');
    printf("%s", "|___");
    printf("%s %3.1f %d\n", root->data.name, root->data.score, root->height);
    display_tree(root->right, prelen + 4);    
    display_tree(root->left, prelen + 4);
  }
}