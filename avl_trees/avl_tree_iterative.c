/* 
 * Code example for CP264 Data Structures II
 * AVL tree insert and delete operations, using iterative algorithms,
 * HBF
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node {
  int key;
  int height;
  struct node *left;
  struct node *right;
} tnode;

int max(int a, int b);
int height(tnode *root);
int get_height(tnode *root);
int balance_factor(tnode *root);
tnode *new_node(int val);
void print_inorder(tnode *root);
void print_tree(tnode *root, int prelen);
void clean_tree(tnode **rootp);
void rotate_left(tnode **rootp);
void rotate_right(tnode **rootp);
void insert(tnode **rootp, int val);
void delete(tnode **rootp, int val);
tnode *search(tnode *root, int val);

int main() {
  // build AVL tree by insertion
  tnode *root = NULL;
  insert(&root, 9);
  insert(&root, 5);
  insert(&root, 10);
  insert(&root, 0);
  insert(&root, 6);
  insert(&root, 11);
  insert(&root, -1);
  insert(&root, 1);
  insert(&root, 2);

  // print AVL tree in 2D style
  print_tree(root, 0);
  printf("\nin-order traversal of the constructed AVL tree is \n");
  print_inorder(root);

  // build AVL tree by insertion
  delete(&root, 10);
  printf("\nafter deletion of 10\n");
  print_tree(root, 0);
  printf("\nin-order traversal after deletion of 10 \n");
  print_inorder(root);

  // AVL tree search
  tnode *np = search(root, 5);
  if (np)
    printf("\nsearch: %d, found %d\n", 5, np->key);

  // clean tree
  clean_tree(&root);
  return 0;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

int height(tnode *root) {
  if (root == NULL)
    return 0;
  else
    return root->height;
}

int balance_factor(tnode* np) {
  if (np == NULL)
    return 0;
  return height(np->left) - height(np->right);
}

tnode *new_node(int key) {
  tnode* node = (tnode*) malloc(sizeof(tnode));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

tnode *search(tnode *tnp, int val) {
  while (tnp) {
    if (val == tnp->key) {
      return tnp;
    } else if (val < tnp->key)
      tnp = tnp->left;
    else
      tnp = tnp->right;
  }
  return NULL;
}

void rotate_right(tnode **yp) {
  tnode *y = *yp;
  tnode *x = y->left;
  tnode *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  *yp = x;
}

void rotate_left(tnode **xp) {
  tnode *x = *xp;
  tnode *y = x->right;
  tnode *T2 = y->left;
  
  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  *xp = y;
}

//totally iterative, bst insert and avl rotation
void insert(tnode **rootp, int val) {
  tnode *parent = NULL, *tnp = *rootp;
  tnode *hctnp_parent = NULL, *hctnp = tnp;
  tnode *critical_node_parent = NULL, *critical_node = NULL;
  int is_height_change = 0;
  int balance = 0;

  // 1. Perform the normal BST insertion
  if (*rootp == NULL) {
    *rootp = new_node(val);
    return;

  } else {

    while (1) {

      if (val == tnp->key) {
        printf("\nThe same key value is found");
        return;
      }

      else if (val < tnp->key) {
        if (height(tnp->left) >= height(tnp->right)) {
          if (is_height_change == 0) {
            hctnp_parent = parent;
            hctnp = tnp;
            is_height_change = 1;
          }
        } else {
          is_height_change = 0;
          hctnp = NULL;
          hctnp_parent = NULL;
        }

        if (tnp->left == NULL) {
          tnp->left = new_node(val);
          parent = tnp;
          tnp = tnp->left;
          break;
        } else {
          parent = tnp;
          tnp = tnp->left;
        }
      }

      else {

        if (height(tnp->right) >= height(tnp->left)) {
          if (is_height_change == 0) {
            hctnp_parent = parent;
            hctnp = tnp;
            is_height_change = 1;
          }
        } else {
          is_height_change = 0;
          hctnp = NULL;
          hctnp_parent = NULL;
        }

        if (tnp->right == NULL) {
          tnp->right = new_node(val);
          parent = tnp;
          tnp = tnp->right;
          break;
        } else {
          parent = tnp;
          tnp = tnp->right;
        }
      }
    }

    //update height of nodes on the affected path
    tnp = hctnp;
    while (tnp) {
      if (val == tnp->key)
        break;
      else if (val < tnp->key) {
        if (tnp->left)
          tnp->height = tnp->height + 1;
        tnp = tnp->left;
      } else {
        if (tnp->right)
          tnp->height = tnp->height + 1;
        tnp = tnp->right;
      }
    }

    //find the critical node and its parent
    tnp = hctnp;
    parent = hctnp_parent;
    while (tnp) {
      if (val == tnp->key)
        break;
      else {
        balance = balance_factor(tnp);
        if (balance < -1 || balance > 1) {
          critical_node_parent = parent;
          critical_node = tnp;
        }
        parent = tnp;
        if (val < tnp->key)
          tnp = tnp->left;
        else
          tnp = tnp->right;
      }
    }
  }

  //set the address reference of critical node pointer
  tnode **critical_node_parent_rootp = NULL;
  if (critical_node_parent) {
    if (critical_node_parent->left == critical_node)
      critical_node_parent_rootp = &critical_node_parent->left;
    else
      critical_node_parent_rootp = &critical_node_parent->right;
  } else {
    critical_node_parent_rootp = rootp;
  }

  // Get the balance factor at the critical node and do rotations accordingly
  balance = balance_factor(critical_node);
  if (balance > 1) {
    if (balance_factor(critical_node->left) >= 0)  // Right Case
      rotate_right(critical_node_parent_rootp);
    else {
      rotate_left(&critical_node->left);
      rotate_right(critical_node_parent_rootp);
    }
  } else if (balance < -1) {
    if (balance_factor(critical_node->right) <= 0)
      rotate_left(critical_node_parent_rootp);
    else {
      rotate_right(&critical_node->right);
      rotate_left(critical_node_parent_rootp);
    }
  }

  //update heights after rotations for nodes on the affected nodes from the height change start node to the critical_node_parent
  tnp = hctnp;
  if (critical_node_parent) {
    while (tnp && tnp != critical_node_parent) {
      if (val < tnp->key) {
        if (tnp->left)
          tnp->height = tnp->height - 1;
        tnp = tnp->left;
      } else {
        if (tnp->right)
          tnp->height = tnp->height - 1;
        tnp = tnp->right;
      }

    }
    critical_node_parent->height = critical_node_parent->height - 1;
  }
}

//totally iterative, bst delete and avl rotation
void delete(tnode **rootp, int val) {
  tnode *tnp = *rootp, *parent = NULL, *mtnp = NULL, *mparent = NULL, *stnp,
      *sparent;
  tnode *hctnp = NULL, *hctnp_parent = NULL;
  tnode *critical_node_parent = NULL, *critical_node = NULL;

  int is_height_change = 0;
  int balance = 0;

  // search to find
  while (tnp) {
    if (val == tnp->key) {
      break;

    } else if (val < tnp->key) {

      if (height(tnp->left) > height(tnp->right)) {
        if (is_height_change == 0) {
          hctnp_parent = parent;
          hctnp = tnp;
          is_height_change = 1;
        }
      } else {
        is_height_change = 0;
        hctnp = NULL;
        hctnp_parent = NULL;
      }

      parent = tnp;
      tnp = tnp->left;

    } else {

      if (height(tnp->left) < height(tnp->right)) {
        if (is_height_change == 0) {
          hctnp_parent = parent;
          hctnp = tnp;
          is_height_change = 1;
        }
      } else {
        is_height_change = 0;
        hctnp = NULL;
        hctnp_parent = NULL;
      }

      parent = tnp;
      tnp = tnp->right;
    }
  }

  if (tnp == NULL) { //not found
    return;
  }
  else {             //found

    mparent = parent;
    mtnp = tnp;
    if (mtnp->left == NULL && mtnp->right == NULL) {  //case 1.
      if (mparent == NULL) {
        *rootp = NULL;
        return;
      } else {
        if (mparent->left == mtnp)
          mparent->left = NULL;
        else
          mparent->right = NULL;
      }

      sparent = mparent;
    }

    else if (mtnp->left != NULL && mtnp->right == NULL) { //case 2.
      if (mparent == NULL) {
        *rootp = mtnp->left;
        return;
      } else {
        if (mparent->left == mtnp)
          mparent->left = mtnp->left;
        else
          mparent->right = mtnp->left;
      }
      sparent = mparent;
    }

    else if (mtnp->left == NULL && mtnp->right != NULL) { //case 3
      if (mparent == NULL) {
        *rootp = mtnp->right;
        return;
      } else {
        if (mparent->left == mtnp)
          mparent->left = mtnp->right;
        else
          mparent->right = mtnp->right;
      }
      sparent = mparent;
    }

    else {   //case 4 mtnp->left != NULL && mtnp->right != NULL)

      if (height(mtnp->left) < height(mtnp->right)) {
        if (is_height_change == 0) {
          hctnp_parent = mparent;
          hctnp = mtnp;
          is_height_change = 2;
        }

      } else {
        is_height_change = 0;
        hctnp = NULL;
        hctnp_parent = NULL;
      }

      //find the smallest node in right subtree
      parent = mtnp;
      tnp = mtnp->right;

      while (tnp->left) {
        if (height(tnp->left) > height(tnp->right)) {
          if (is_height_change == 0) {
            hctnp_parent = parent;
            hctnp = tnp;
            is_height_change = 1;
          } else {
            is_height_change = 0;
            hctnp = NULL;
            hctnp_parent = NULL;
          }
        }
        parent = tnp;
        tnp = tnp->left;
      }

      //found and set
      sparent = parent;
      stnp = tnp;

      //update height for deleting
      if (is_height_change != 0) {
        tnp = hctnp;
        while (tnp && tnp != sparent) {
          tnp->height = tnp->height - 1;
          if (sparent->key == tnp->key) {
            break;
          } else if (sparent->key < tnp->key) {
            tnp = tnp->left;
          } else {
            tnp = tnp->right;
          }
        }
        sparent->height = sparent->height - 1;
      }

      //extract the smallest and replace the matched node mtnp
      stnp->left = mtnp->left;
      stnp->right = mtnp->right;
      stnp->height = mtnp->height;

      if (mparent == NULL)
        *rootp = stnp;
      else if (mparent->left == mtnp)
        mparent->left = stnp;
      else
        mparent->right = stnp;
    }

    free(mtnp);

    //find the critical node and its parent
    if (is_height_change != 0) {
      parent = hctnp_parent;
      tnp = hctnp;

      while (tnp && tnp != sparent) {
        balance = balance_factor(tnp);
        if (balance < -1 || balance > 1) {
          critical_node_parent = parent;
          critical_node = tnp;
        }

        parent = tnp;
        if (sparent->key == tnp->key)
          break;
        else if (sparent->key < tnp->key)
          tnp = tnp->left;
        else
          tnp = tnp->right;
      }
    }
  }

  //set the address reference of critical node pointer
  tnode **critical_node_parent_rootp = NULL;
  if (critical_node_parent) {
    if (critical_node_parent->left == critical_node)
      critical_node_parent_rootp = &critical_node_parent->left;
    else
      critical_node_parent_rootp = &critical_node_parent->right;
  } else {
    critical_node_parent_rootp = rootp;
  }

  // Get the balance factor at the critical node and do rotations accordingly
  balance = balance_factor(critical_node);
  if (balance > 1) {
    if (balance_factor(critical_node->left) >= 0)  // Right Case
      rotate_right(critical_node_parent_rootp);
    else {
      rotate_left(&critical_node->left);
      rotate_right(critical_node_parent_rootp);
    }
  } else if (balance < -1) {
    if (balance_factor(critical_node->right) <= 0)
      rotate_left(critical_node_parent_rootp);
    else {
      rotate_right(&critical_node->right);
      rotate_left(critical_node_parent_rootp);
    }
  }

  //update height from hctnp to critical point parent.
  tnp = hctnp;
  if (critical_node_parent) {
    while (tnp != critical_node_parent) {
      if (critical_node_parent->key < tnp->key) {
        if (tnp->left)
          tnp->height = tnp->height - 1;
        tnp = tnp->left;
      } else {
        if (tnp->right)
          tnp->height = tnp->height - 1;
        tnp = tnp->right;
      }
    }
    critical_node_parent->height = critical_node_parent->height - 1;
  }
}

void clean_tree(tnode **rootp) {
  if (*rootp) {
    tnode *np = *rootp;
    if (np->left)
      clean_tree(&np->left);
    if (np->right)
      clean_tree(&np->right);
    free(np);
  }
  *rootp = NULL;
}

void print_inorder(tnode *root) {
  if (root != NULL) {
    print_inorder(root->left);
    printf("%d ", root->key);
    print_inorder(root->right);
  }
}

void print_tree(tnode *root, int prelen) {
  int i;
  if (root != NULL) {
    for (i = 0; i < prelen; i++)
      printf("%c", ' ');
    printf("%s", "|___");
    printf("%d\n", root->key);
    print_tree(root->right, prelen + 4);
    print_tree(root->left, prelen + 4);
  }
}

/*
|___9
    |___10
        |___11
    |___1
        |___5
            |___6
            |___2
        |___0
            |___-1

in-order traversal of the constructed AVL tree is
-1 0 1 2 5 6 9 10 11
after deletion of 10
|___9
    |___11
    |___1
        |___5
            |___6
            |___2
        |___0
            |___-1

in-order traversal after deletion of 10
-1 0 1 2 5 6 9 11
search: 5, found 5
 */

