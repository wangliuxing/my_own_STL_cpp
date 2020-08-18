#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "51-Tree.h"
#include "35-Static_Link_Queue.h"
#include "19-Array.cpp"
using namespace std;
using namespace Wang;
namespace Wang
{
    enum BTNodePos
    {
        ANY,
        LEFT,
        RIGHT
    };
    enum BTTraversal//定义四种线索化枚举量，
    {
        PreOrder,
        InOrder,
        PostOrder,
        LevelOrder
    };
    /**    二叉树节点的定义           */
    /**    二叉树节点的定义           */
    template <typename T>
    class BTreeNode : public TreeNode<T>
    {
    public:
        BTreeNode<T>* left;
        BTreeNode<T>* right;
        BTreeNode()
        {
            left = NULL;
            right = NULL;
        }
        static BTreeNode<T>* NewNode()
        {
            BTreeNode<T>* ret = new BTreeNode<T>();
            if(ret != NULL)
            {
                ret->m_flag = true;
            }
            return ret;
        }
    };
    /**    二叉树节点的定义完成          */

    /**    二叉树的定义          */ /**    二叉树的定义          */
    /**    二叉树的定义          */ /**    二叉树的定义          */
    template <typename T>
    class BTree : public Tree<T>
    {
    protected:
        LinkQueue<BTreeNode<T>*> m_queue;//用于遍历的
        virtual BTreeNode<T>* find(BTreeNode<T>* node,const T& value) const
        {
            BTreeNode<T>* ret = NULL;
            if(node!=NULL)
            {
                if(node->value == value)
                {
                    ret = node;
                }
                else
                {
                    if(ret == NULL)
                    {
                        ret = find(node->left,value);
                    }
                    if(ret == NULL)
                    {
                        ret = find(node->right,value);
                    }
                }
            }
            return ret;
        }
        virtual BTreeNode<T>* find(BTreeNode<T>* node,BTreeNode<T>* obj) const
        {
            BTreeNode<T>* ret = NULL;
            if(node == obj)
            {
                ret = node;
            }
            else
            {
                if(node!=NULL)
                {
                    if(ret == NULL)
                    {
                        ret = find(node->left,obj);
                    }
                    if(ret == NULL)
                    {
                        ret = find(node->right,obj);
                    }
                }
            }
            return ret;
        }
        virtual bool insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
        {//插入的节点为n；父节点为np
            bool ret = true;
            if(pos == ANY)
            {
                if(np->left ==NULL)
                {
                    np->left = n;
                }
                else if(np->right ==NULL)
                {
                    np->right = n;
                }
                else
                {
                    ret = false;
                }
            }
            else if(pos == LEFT)
            {
                if(np->left ==NULL)
                {
                    np->left = n;
                }
                else
                {
                    ret = false;
                }
            }
            else if(pos == RIGHT)
            {
                if(np->right ==NULL)
                {
                    np->right = n;
                }
                else
                {
                    ret = false;
                }
            }
            else
            {
                ret = false;
            }
            return ret;
        }
        virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
        {
            ret = new BTree<T>();
            if(ret != NULL)
            {
                if(node == this->m_root)
                {
                    this->m_root = NULL;
                }
                else
                {
                    BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
                    if(parent->left == node)
                    {
                        parent->left = NULL;
                    }
                    if(parent->right == node)
                    {
                        parent->right = NULL;
                    }
                    node->parent = NULL;
                }
                ret->m_root = node;
            }
            else
            {
                //抛出异常
            }
        }
        void free(BTreeNode<T>* node)
        {
            if(node != NULL)
            {
                free(node->left);
                free(node->right);
                if(node->flag() == true)
                {
                    delete node;
                }
            }
        }
        int degree(BTreeNode<T>* node)const
        {
            int ret = 0;
            if(node != NULL)
            {
            //  只有当前节点不为零才能计算度数
            /*  int l = height(node->left);
                int r = height(node->right);
                ret = (!!node->left + !!node->right);
                if(ret<l)
                {
                    ret = l;
                }
                if(ret<r)
                {
                    ret = r;
                }
                */
                ret = (!!node->left + !!node->right);
                if(ret < 2)
                {
                    int d = degree(node->left);
                    if(ret < d)
                    {
                        ret = d;
                    }
                }
                if(ret < 2)
                {
                    int d = degree(node->right);
                    if(ret < d)
                    {
                        ret = d;
                    }
                }
            }
            return ret;
        }
        int count(BTreeNode<T>* node)const
        {
            int ret = 0;
            if(node != NULL)
            {
                ret = count(node->left) + 1 + count(node->right);
            }
            return ret;
        }
        int height(BTreeNode<T>* node)const
        {
            int ret = 0;
            if(node != NULL)
            {
                int l = height(node->left);
                int r = height(node->right);
                ret = ((l>r)?l:r)+1;
            }
            return ret;
        }
        void preordertraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
        {//用队列记录节点压入的顺序
            if(node!=NULL)
            {
                queue.add(node);//头结点首先入队
                preordertraversal(node->left,queue);
                preordertraversal(node->right,queue);
            }
        }
        void inordertraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
        {
            if(node!=NULL)
            {
                inordertraversal(node->left,queue);
                queue.add(node);
                inordertraversal(node->right,queue);
            }
        }
        void postordertraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
        {
            if(node!=NULL)
            {
                postordertraversal(node->left,queue);
                postordertraversal(node->right,queue);
                queue.add(node);
            }
        }
        void LevelOrderTraversal(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& queue)
        {//层次遍历
            if(node!=NULL)
            {
                LinkQueue<BTreeNode<T>*> tmp;
                tmp.add(node);
                queue.clear();
                while(tmp.length()>0)
                {
                    BTreeNode<T>* n = tmp.front();
                    if(n->left != NULL) tmp.add(n->left);
                    if(n->right != NULL) tmp.add(n->right);
                    tmp.remove();
                    queue.add(n);
                }
            }
        }
        BTreeNode<T>* clone(BTreeNode<T>* node)const
        {
            BTreeNode<T>* ret = NULL;
            if(node != NULL)
            {
                ret = BTreeNode<T>::NewNode();
                if(ret != NULL)
                {
                    ret->value = node->value;//比较当前结点的值
                    ret->left = clone(node->left);
                    ret->right = clone(node->right);//对左右指针进行赋值
                    if(ret->left != NULL)
                    {
                        ret->left->parent = ret;//建立父子关系，对parent进行赋值
                    }
                    if(ret->right != NULL)
                    {
                        ret->right->parent = ret;
                    }
                }
                else
                {
                    //抛出异常
                }
            }

            return ret;
        }
        bool equal(BTreeNode<T>* node1, BTreeNode<T>* node2)const
        {
            if(node1 == node2)
            {
                return true;
            }
            else if((node1!=NULL)&&(node2!=NULL))
            {
                return (node1->value == node2->value)&&equal(node1->left,node2->left)&&equal(node1->right,node2->right);
            }
            else{return false;}
        }
        BTreeNode<T>* add(BTreeNode<T>* lh,BTreeNode<T>* rh)const
        {
            BTreeNode<T>* ret = NULL;
            if((lh==NULL)&&(rh!=NULL))
            {
                ret = clone(rh);
            }
            else if((lh!=NULL)&&(rh==NULL))
            {
                ret = clone(lh);
            }
            else if((lh!=NULL)&&(rh!=NULL))
            {
                ret = BTreeNode<T>::NewNode;
                if(ret!=NULL)
                {
                    ret->value = lh->value + rh->value;//对当前结点进行增加
                    ret->left = add(lh->left,rh->left);
                    ret->right = add(lh->right,rh->right);
                    if(ret->left!=NULL)//加完之后对所有数据进行关系链接
                    {
                        ret->left->parent = ret;
                    }
                    if(ret->right!=NULL)
                    {
                        ret->right->parent = ret;
                    }
                }
                else{}
            }
            return ret;
        }
        void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*>& queue)
        {//指定层次遍历方式
            switch(order)
            {
            case PostOrder:
                postordertraversal(root(),queue);
                break;
            case InOrder:
                inordertraversal(root(),queue);
                break;
            case PreOrder:
                preordertraversal(root(),queue);
                break;
            case LevelOrder://层次遍历函数
                LevelOrderTraversal(root(),queue);
                break;
            default:
                //抛出异常
                break;
            }
        }
        BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*>& queue)
        {
            //返回双向链表的首节点地址
            BTreeNode<T>* ret= NULL;
            if(queue.length()>0)//进行初始化工作
            {
                ret = queue.front();
                BTreeNode<T>* slider= queue.front();
                queue.remove();
                slider->left = NULL;

            while(queue.length()>0)
            {
                slider->right = queue.front();
                queue.front()->left = slider;
                slider = queue.front();
                queue.remove();
            }
            slider->right = NULL;//尾节点置为空
            }
            return ret;//返回头结点，通过slider进行队列的链接
        }
    public:
        virtual bool insert(TreeNode<T>* node, BTNodePos pos)//插入的位置为pos
        {
            bool ret = true;
            if(node!=NULL)
            {
                if(this->m_root == NULL)
                {
                    this->m_root = node;
                    node->parent = NULL;
                }
                else
                {
                    BTreeNode<T>* m = find(node->parent);
                    if(m != NULL)
                    {
                       ret = insert(dynamic_cast<BTreeNode<T>*>(node),m,pos);//调用protected成员
                    }
                    else
                    {
                        //抛出异常
                    }
                }
            }
            else
            {
                //抛出异常
            }
            return ret;
        }
        bool insert(TreeNode<T>* node)
        {
            return insert(node,ANY);//插入的位置没有要求
        }
        virtual bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
        {
            bool ret = true;
            BTreeNode<T>* node = BTreeNode<T>::NewNode();
            if(node != NULL)
            {
                node->value = value;
                node->parent = parent;
                ret = insert(node,pos);
                if(ret != true)//判断是否插入成功
                {
                    delete node;//删除堆空间的值
                }
            }
            else
            {
            //抛出异常
            }
            return ret;
        }
        virtual bool insert(const T& value, TreeNode<T>* parent)//任意位置插入
        {
            return insert(value,parent,ANY);
        }
        virtual Sharedpoint< Tree<T> > remove(const T& value)
        {
            BTree<T>* ret = NULL;
            BTreeNode<T>* node = find(value);
            if(node==NULL)
            {
                //抛出异常
            }
            else
            {
                remove(node,ret);
                m_queue.clear();
            }
            return ret;
        }
        virtual Sharedpoint< Tree<T> > remove(TreeNode<T>* node)
        {
            BTree<T>* ret = NULL;
            node = find(node);
            if(node != NULL)
            {
                remove(dynamic_cast<BTreeNode<T>*>(node),ret);
                m_queue.clear();
            }
            else
            {
                //抛出异常
            }
            return ret;
        }
        virtual BTreeNode<T>* find(const T& value)const
        {
            return find(root(),value);
        }
        virtual BTreeNode<T>* find(TreeNode<T>* node)const
        {
            return find(root(),dynamic_cast<BTreeNode<T>*>(node));
        }
        virtual BTreeNode<T>* root()const
        {
            return dynamic_cast<BTreeNode<T>*>(this->m_root);
        }
        virtual int degree() const
        {
            return degree(root());
        }
        virtual int count() const
        {
            return count(root());
        }
        virtual int height() const
        {
            return height(root());
        }
        virtual void clear()
        {
            free(root());

            m_queue.clear();

            this->m_root = NULL;
        }
        bool begin()
        {
            bool ret = (this->m_root != NULL);
            if(ret)
            {
                m_queue.clear();
                m_queue.add(root());
            }
            return ret;
        }
        bool next()
        {
            bool ret = (m_queue.length() > 0);
            if(ret)
            {
                BTreeNode<T>* node = m_queue.front();
                m_queue.remove();
                if(node->left != NULL) m_queue.add(node->left);
                if(node->right != NULL) m_queue.add(node->right);
            }
            return ret;
        }
        T current()
        {
            if(!end())
            {
                return m_queue.front()->value;
            }
        }
        bool end()
        {
            return (m_queue.length()==0);
        }
        Sharedpoint< Array<T> >traversal(BTTraversal order)//遍历二叉树
        {
            DynamicArray<T>* ret = NULL;
            LinkQueue<BTreeNode<T>*> queue;//保存遍历节点的次序
            switch(order)
            {
            case PostOrder:
                postordertraversal(root(),queue);
                break;
            case InOrder:
                inordertraversal(root(),queue);
                break;
            case PreOrder://先序遍历函数
                preordertraversal(root(),queue);
                break;
            case LevelOrder://层次遍历函数
                LevelOrderTraversal(root(),queue);
                break;
            default:
                //抛出异常
                break;
            }//queue保存的是遍历次序
            ret = new DynamicArray<T>(queue.length());
            if(ret != NULL)//通过数组保存遍历次序里面的值，也可以通过队列保存
            {
                for(int i=0; i<ret->length(); i++, queue.remove())
                {
                    ret->set(i,queue.front()->value);//通过数组保存遍历次序里面的值
                }
            }
            else
            {
                //抛出异常
            }

            return ret;
        }
        Sharedpoint< BTree<T> > clone()const//复制一棵树
        {
            BTree<T>* ret = new BTree<T>();
            if(ret != NULL)
            {
                ret->m_root = clone(root());
            }
            else
            {
                //抛出异常
            }
            return ret;
        }
        bool operator ==(const BTree<T>& btree)
        {
            return equal(root(),btree.root());
        }
        bool operator !=(const BTree<T>& btree)
        {
            return !(*this != btree);
        }
        Sharedpoint< BTree<T> > add(const BTree<T>& btree)const
        {
            BTree<T>* ret = new BTree<T>();
            if(ret != NULL)
            {
                ret->m_root = add(root(),btree.root());
            }
            else
            {
                //抛出异常
            }
            return ret;
        }
        BTreeNode<T>* thread(BTTraversal order)//二叉树转化为双向链表
        {
            BTreeNode<T>* ret = NULL;
            LinkQueue<BTreeNode<T>*> queue;
            traversal(order,queue);//获取遍历次序保存在queue中
            ret = connect(queue);//把queue中的数据元素进行连接，返回指向双向链表的头结点地址
            this->m_root = NULL;//把当前链表置空
            m_queue.clear();
            return ret;
        }
        ~BTree()
        {
            clear();
        }
    };
/**
BTree<int> bt;
    BTreeNode<int>* n = NULL;
    bt.insert(1,NULL);
    n = bt.find(1);
    bt.insert(2,n);
    bt.insert(3,n);

    n = bt.find(2);
    bt.insert(4,n);
    bt.insert(5,n);

    n = bt.find(4);
    bt.insert(8,n);
    bt.insert(9,n);

    n = bt.find(5);
    bt.insert(10,n);

    n = bt.find(3);
    bt.insert(6,n);
    bt.insert(7,n);

    n = bt.find(6);
    bt.insert(11,n,LEFT);
    Sharedpoint< BTree<int> > btclone = bt.clone();
    /*
    int a[]={8,9,10,11,7};

    Sharedpoint< Tree<int> > sp = bt.remove(3);

    for(int i=0;i<5;i++)
    {
        TreeNode<int>* node = sp->find(a[i]);
        while(node)
        {
            cout<< node->value<<" ";
            node = dynamic_cast< BTreeNode<int>* >(node->parent);
        }
        cout<<endl;
    }
    for(bt.begin();!bt.end();bt.next())
    {
        cout<<bt.current()<<" ";
    }
    cout<<endl;
    Sharedpoint< Array<int> > sp = NULL;
    sp = bt.traversal(PreOrder);
    for(int i=0;i<(*sp).length();i++)
    {
        cout<<(*sp)[i]<<" ";
    }
    cout<<endl;
    Sharedpoint< Array<int> > tr = bt.traversal(LevelOrder);
    for(int i=0;i<(*sp).length();i++)
    {
        cout<<(*sp)[i]<<" ";
    }
    cout<<endl;
    BTreeNode<int>*head = bt.thread(LevelOrder);
    while(head->right !=NULL)
    {
        head=head->right;
    }
    while(head!=NULL)
    {
        cout<<head->value<<" ";
        head=head->left;
    }
    cout<<endl;
    return 0;


*/


}

#endif // BTREE_H
