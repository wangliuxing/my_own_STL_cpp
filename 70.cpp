#include <iostream>
#include "52-BTree.h"

using namespace std;
using namespace Wang;
/**
template < typename T >
class BTreeNode
{
public:
    T value;
    BTreeNode* left;
    BTreeNode* right;
    BTreeNode* parent;
    BTreeNode()
    {
        left = NULL;
        right = NULL;
        left = NULL;
    }
};
*/
template < typename T >
BTreeNode<T>* createTree()
{
    static BTreeNode<int> ns[9];//创建了有9个对象的数组

    for(int i=0; i<9; i++)
    {
        ns[i].value = i;
        ns[i].parent = NULL;
        ns[i].left = NULL;
        ns[i].right = NULL;
    }

    ns[0].left = &ns[1];
    ns[0].right = &ns[2];
    ns[1].parent = &ns[0];
    ns[2].parent = &ns[0];

    ns[1].left = &ns[3];
    ns[1].right = NULL;
    ns[3].parent = &ns[1];

    ns[2].left = &ns[4];
    ns[2].right = &ns[5];
    ns[4].parent = &ns[2];
    ns[5].parent = &ns[2];

    ns[3].left = NULL;
    ns[3].right = &ns[6];
    ns[6].parent = &ns[3];

    ns[4].left = &ns[7];
    ns[4].right = NULL;
    ns[7].parent = &ns[4];

    ns[5].left = &ns[8];
    ns[5].right = NULL;
    ns[8].parent = &ns[5];

    return ns;
}

template < typename T >
void printInOrder(BTreeNode<T>* node)
{//中序遍历
    if( node != NULL )
    {
        printInOrder(node->left);

        cout << node->value <<" ";

        printInOrder(node->right);
    }
}

template < typename T >
void printDualList(BTreeNode<T>* node)
{//循环打印链表
    BTreeNode<T>* g = node;

    cout << "head -> tail: " << endl;

    while( node != NULL )
    {
        cout << node->value << " ";

        g = node;

        node = node->right;
    }

    cout << endl;

    cout << "tail -> head: " << endl;

    while( g != NULL )
    {
        cout << g->value << " ";

        g = g->left;
    }

    cout << endl;
}
template<typename T>
BTreeNode<T>* delOdd1(BTreeNode<T>* node)
{
    BTreeNode<T>* ret = NULL;
    if(node!=NULL)
    {
        if(((node->left != NULL)&&(node->right == NULL))||
           ((node->left == NULL)&&(node->right != NULL)))
        {//node为单度结点
            BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
            BTreeNode<T>*& node_child = (node->left != NULL)?(node->left):(node->right);
            if(parent != NULL)
            {
                BTreeNode<T>*& parent_child = (parent->left == node)?(parent->left):(parent->right);
                //找到一个插入位置
                parent_child = node_child;
                node_child->parent = parent;
            }
            else
            {
                node_child->parent = NULL;
            }
            ret = delOdd1(node_child);//开始从node_child找单度结点
            if(node->flag())
            {
                delete node;
            }
        }
        else
        {
            delOdd1(node->left);
            delOdd1(node->right);
            ret = node;//返回当前结点
        }
    }
    return ret;
}
template<typename T>
void delOdd2(BTreeNode<T>* &node)
{
    if(node!=NULL)
    {
        if(((node->left != NULL)&&(node->right == NULL))||
           ((node->left == NULL)&&(node->right != NULL)))
        {//判断单度结点
            BTreeNode<T>* node_child = (node->left != NULL)?(node->left):(node->right);
            if(node->flag())
            {
                delete node;
            }
            node = node_child;//node是node_child的别名
            delOdd2(node);
        }
        else
        {
            delOdd1(node->left);
            delOdd1(node->right);
        }
    }
}
template<typename T>
void inorderthread(BTreeNode<T>* node, BTreeNode<T>*& pre)
{
    if(node != NULL)
    {
        inorderthread(node->left,pre);//中序遍历node结点的左子树，并进行指针的链接
        node->left = pre;
        if(pre != NULL)
        {
            pre->right = node;
        }//node与pre指针的链接
        pre = node;
        inorderthread(node->right,pre);//中序遍历node结点的右子树，并进行指针的链接
    }
}

template<typename T>
BTreeNode<T>* inorderthread1(BTreeNode<T>* node)
{
    BTreeNode<T>* pre = NULL;
    inorderthread(node,pre);//node指向链表中的一个位置
    while((node!=NULL)&&(node->left != NULL))//找到首节点
    {
        node = node->left;
    }
    return node;//返回首节点的地址
}
template<typename T>
void inorderthread(BTreeNode<T>* node,BTreeNode<T>*& head,BTreeNode<T>*& tail)
{
    if(node!=NULL)
    {
        BTreeNode<T>* h = NULL;
        BTreeNode<T>* t = NULL;
        inorderthread2(node->left,h,t);//node结点的左边进行链表化
        node->left = t;
        if(t!=NULL)
        {
            t->right = node;
        }
        head = (h != NULL)? h : node;
        h = NULL;
        t = NULL;
        inorderthread2(node->right,h,t);//node结点的右边进行链表化
        node->right = h;
        if(h!=NULL)
        {
            h->left = node;
        }
        tail = (t != NULL)? t : node;
    }
}
template<typename T>
BTreeNode<T>* inorderthread2(BTreeNode<T>* node)
{
    BTreeNode<T>* head = NULL;
    BTreeNode<T>* tail = NULL;
    inorderthread(node,head,tail);//node指向链表中的一个位置

    return head;//返回双向链表的头结点
}
int main()
{
    BTreeNode<int>* ns = createTree<int>();

    printInOrder(ns);

    cout << endl;

    ns = delOdd1(ns);

    printInOrder(ns);
    cout<<endl;

    int a[]={6,7,8};

    for(int i=0;i<3;i++)
    {
        TreeNode<int>* n = ns + a[i];
        while(n!=NULL)
        {
            cout<<n->value<<" ";
            n = n->parent;
        }
        cout<<endl;
    }
    cout<<endl;

    delOdd2(ns);

    printInOrder(ns);

    cout<<endl;

    ns = inorderthread1(ns);

    printDualList(ns);

    return 0;
}

