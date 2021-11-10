#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "hash.h"

int hash(char* word) {
  unsigned int hash = 0, i;
  for (i = 0; word[i] != '\0'; i++) {
    hash = 31 * hash + word[i];
  }
  return hash % htsize;
}

HTNODE *new_hashnode(char *name, int value) {
    HTNODE *hnode = (HTNODE *) malloc(sizeof(HTNODE));
    strcpy(hnode->name, name);
    hnode->value = value;
    hnode->next = NULL;
    return hnode;
}

HASHTABLE *new_hashtable(int size) {
    HASHTABLE *htable = (HASHTABLE *) malloc(sizeof(HASHTABLE));
    htable->size = size;
    htable->count = 0;
    htable->hnp = (HTNODE **) malloc(sizeof(HTNODE) * size);
    for (int i = 0; i < size; i++)
        htable->hnp[i] = NULL;
    return htable;
}

HTNODE *search(HASHTABLE *ht, char *name) { 
    // Get hash of key to search
    int index = hash(name);
    // Hashnode exists at index of the hash
    if (ht->hnp[index])
    {
        // Get the hashnode to iterate through
        // underlying array structure
        HTNODE *tmp = ht->hnp[index];
        while (tmp)
        {
            // Found key
            if (strcmp(tmp->name, name) == 0)
                return tmp;
            tmp = tmp->next;
        }
    }
    return NULL;
}

int insert(HASHTABLE *ht, HTNODE *np) {
    //printf("::> In insert()...\n");
    int index = hash(np->name);
    // Hash exists in the hashtable
    if (ht->hnp[index])
    {
        //printf("::> Hash exists..\n");
        HTNODE *tmp = ht->hnp[index];
        while (tmp)
        {
            if (strcmp(tmp->name, np->name) == 0)
            {
                tmp->value = np->value;
                return 0;
            }
            tmp = tmp->next;
        }
        tmp = np;
        ht->count++;
        return 1;
    }
    //printf("::> Hash not in table..\n");
    // Hash not in table, set equal to new hashnode
    ht->hnp[index] = np;
    ht->count++;

    //printf("::> End of insert()..\n");
    return 1;
}

int delete(HASHTABLE *ht, char *name) {
    int index = hash(name);
    if (ht->hnp[index])
    {
        HTNODE *tmp = ht->hnp[index];
        HTNODE *prev = NULL;

        while (tmp)
        {

            if (strcmp(tmp->name, name) == 0)
            {
                if (prev)
                    prev->next = tmp->next;
                if (tmp == ht->hnp[index])
                    ht->hnp[index] = NULL;
                free(tmp);
                ht->count--;
                return 1;
            }
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return 0;
}

void clean_hash(HASHTABLE **htp) {
  if (*htp == NULL) return;
  HASHTABLE *ht = *htp;
  HTNODE *sp = ht->hnp[0], *p, *temp;
  int i;
  for (i = 0; i < ht->size; i++) {
    p = ht->hnp[i];
    while (p) {
      temp = p;  
      p = p->next;
      free(temp);
    }
  ht->hnp[i] = NULL;
  }
  free(ht->hnp);
  ht->hnp = NULL;
  *htp = NULL;
}

void display_hashtable(HASHTABLE *ht, int option) {
  int i = 0;
  HTNODE *p;
  if (option == 0) {
  printf("size:  %d\n", ht->size);
  printf("count: %d\n", ht->count);
  printf("hash data:\nindex: list of the data elements");
  for (i = 0; i < ht->size; i++) {
    p = *(ht->hnp + i);
    if (p)
      printf("\n%2d: ", i);
    
    while (p) {
      printf("(%s, %d) ", p->name, p->value);
      p = p->next;
    }
  }
  printf("\n");
  }
  else {
      
  for (i = 0; i < ht->size; i++) {
    p = *(ht->hnp + i);
    while (p) {
      printf("%s=%d\n", p->name, p->value);
      p = p->next;
    }
  }
      
  }
  
}