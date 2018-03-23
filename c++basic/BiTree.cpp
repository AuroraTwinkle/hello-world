#include<iostream>
#include<cstring>
#include<string.h>
 
using namespace std;
struct BiTree           //构造二叉树节点 
{
    char data;
    struct BiTree *LChild;
    struct BiTree *RChild;
}   tree;
class Tree
{
private:
    void Release(BiTree *R)
    {
        if (R)
        {
            Release(R->LChild);
            Release(R->RChild);
            delete R;
        }
    }
public:
    int Find(char elem, char *arry, int len)            //查找元素,存在返回位置,不存在返回-1; 
    {
        for (int i = 0; i < len; i++)
        {
            if (arry[i] == elem)
                return i;
        }
        return -1;
    }
    BiTree *biTree(char *front, char *center, int len, int &a)      //构建二叉树 
    {
        if (len <= 0 && a != -1)
            return NULL;
        BiTree *temp = new BiTree;
        temp->data = *front;
        int index = Find(*front, center, len);
        if (index != -1)
        {
            temp->LChild = biTree(front + 1, center, index, a);
            temp->RChild = biTree(front + index + 1, center + index + 1, len - index - 1, a);
            return temp;
        }
        else
        {
            a = -1;
            return NULL;
        }
    }
    void PostOrder(BiTree *root)
    {
        if (root != NULL)
        {
            PostOrder(root->LChild);
            PostOrder(root->RChild);
            cout << root->data;
        }
    }
    void LevelOrder(BiTree *root)
    {
        BiTree *queue[1000];
        int f = 0, r = 0;
        if (root != NULL)
        {
            queue[++r] = root;
            while (f != r)
            {
                BiTree *p = queue[++f];
                cout << p->data;
                if (p->LChild != NULL)   queue[++r] = p->LChild;
                if (p->RChild != NULL) queue[++r] = p->RChild;
            }
            cout << endl;
        }
    }
};
 
int main()
{
    int *a = NULL;
    int b = 0;
    a = &b;
    char * preorder = new char[1000];
    char * inorder = new char[1000];
    cin >> preorder;
    cin >> inorder;
    if (strlen(preorder) == strlen(inorder))
    {
        Tree l;
        BiTree * root = l.biTree(preorder, inorder, strlen(inorder), *a);
        if (*a != -1) {
            l.PostOrder(root);
            cout << endl;
            l.LevelOrder(root);
        }
        else
            cout << "error" << endl;
    }
    else
        cout << "error" << endl;
    return 0;
}
