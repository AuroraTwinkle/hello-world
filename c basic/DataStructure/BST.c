#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *lchild,*rchild;
}BSTnode,*BSTree;

void insertBST(BSTree *bst,int key)
{
    BSTree node;
    if(*bst == NULL)
    {
        node = (BSTree)malloc(sizeof(BSTnode));
        node->key = key;
        node->lchild = NULL;
        node->rchild = NULL;
        *bst = node;
    }
    else
    {
        if((*bst)->key > key)
        {
           insertBST(&((*bst)->lchild),key);
        }
        if((*bst)->key < key)
        {
            insertBST(&((*bst)->rchild),key);
        }
    
}}