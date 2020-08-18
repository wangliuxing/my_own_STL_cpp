#ifndef _LINKLIST_H
#define _LINKLIST_H

#include <iostream>
#include "14-list.cpp"

using namespace std;

namespace Wang
{
template<typename T>
class Linklist : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node *next;
    };
   // mutable Node m_header;//头结点只使用next
   mutable struct :  public Object
   {
       char reserved[sizeof(T)];
       Node *next;
   }m_header;
    int m_length;
    Node* position(int i) const    //O(n)
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);
        for(int p=0;p<i;p++)
        {
            ret = ret->next;
        }
        return ret;
    }
    Node *m_current;
    int m_step;
    virtual Node* creat()
    {
        return new Node();
    }
    virtual void destory(Node* pn)
    {
        delete pn ;
    }
public:
    Linklist()
    {
        m_header.next = NULL;
        m_length = 0;//初始化定义的成员变量
        m_step=1;
        m_current = NULL;
    }
    bool insert(const T &e)//在线性表的尾部插入
    {
        return insert(m_length,e);
    }
    bool insert(int i, const T &e)//讲元素插入线性表
    {
        bool ret =((0<=i)&&(i<=m_length));
        if(ret)
        {
            Node *node = creat();
            //creat所调用的函数取决于对象的类型
            if(node!=NULL)
            {
                Node *current = position(i);
             /*   &m_header;
                for(int p=0;p<i;p++)
                {
                    current = current->next;
                }
            */
                node->value = e;
                node->next = current->next;
                current->next=node;
                m_length++;
            }
            else
            {
                //抛出一个异常THROW_EXCPTION(EXCPTION,"No memory to insert element...")
            }
        }
        return ret;
    }
    bool remove(int i)//把i处元素从线性表中删除
    {
        bool ret =((0<=i)&&(i<m_length));
            if(ret)
            {
            Node *current = position(i);
             /*   &m_header;
                for(int p=0;p<i;p++)
                {
                    current = current->next;
                }
            */
                Node* toDel = current->next;
                if(m_current == toDel)
                {
                    m_current = toDel->next;
                }
                current->next = toDel->next;
                m_length--;
                destory(toDel);
            }
            return ret;

    }

    bool set(int i, const T &e)//设置i处元素
    {
        bool ret =((0<=i)&&(i<m_length));
        if(ret)
        {
            Node *current = position(i);
             /*   &m_header;
                for(int p=0;p<i;p++)
                {
                    current = current->next;
                }
            */
                current->next->value = e;
                //当前位置的上一个值的值，因为设置时会从0开始
        }
           return ret;

    }
    T get(int i) const
    {
        T ret;
        if(get(i,ret))
        {
            return ret;
        }
        else
        {
            //抛出异常
        }
    }

   virtual bool get(int i, T &e)const //获取i处元素的值
    {
        bool ret =((0<=i)&&(i<m_length));
        if(ret)
        {
            Node *current = position(i);
             /*   &m_header;
                for(int p=0;p<i;p++)
                {
                    current = current->next;
                }
            */
                e = current->next->value;//current的下一个位置
              //  e = current->value;
        }
           return ret;
    }
    int find(const T &e)const   //O(n)
    {
        int ret = -1;
        int i=0;
        Node *node = m_header.next;
        while(node)
        {
            if( node->value == e)//比较两个test是否相等
            {
                ret = i;
                break;
            }
            else
            {
                node = node->next;
                i++;
            }
        }
        return ret;
    }
    int length() const //获取线性表的长度
    {
        return m_length;
    }
    void clear()//清空线性表//头结点没有值，所以不删除
    {
        while(m_header.next)
        {
            Node *toDel = m_header.next;
            m_header.next = toDel->next;
            m_length--;
            destory(toDel);//父类与子类都有这个函数
        }
        /**
         while(m_length>0)
        {
            remove(0);
        }
        */
    }
   virtual bool move(int i,int step=1)//移动到目标位置
    {
        bool ret = (0<=i)&&(i<m_length)&&(step>0);
        if(ret)
        {
            m_current = position(i)->next;//移动到i位置，为当前位置的下一个位置
            m_step = step;
        }
        return ret;
    }
   virtual bool end()
    {
        return (m_current == NULL);
    }
   virtual T current()
    {
        if(m_current!=NULL)
        {
            return m_current->value;
        }
    /*    else
        {
            //抛出异常THROW_EXCEPTION(EXCEPTION)
        }*/
    }
   virtual bool next()
    {
        int i = 0;
        while((i<m_step)&&(m_current != NULL))
        {
            m_current = m_current->next;
            i++;
        }
        return (i==m_step);
    }
    ~Linklist()
    {
        clear();
    }
};
}
#endif // _LINKLIST_H

//////////////////////////////////////////////
/*class TTest : public Object
{
public:
    TTest()
    {
        throw 0;
    }
};*/
///////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
class Testa : public Object
{
    int i;
public:
    Testa(int v = 0)
    {
        i = v;
    }
    bool operator ==(const Testa& t)
    {
        return (i == t.i);
    }
};
*/
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
int main()
{
//////////////////////////////////////////////
 // Wang::Linklist<TTest> t;
 // cout<<"wang"<<endl;
//////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*    Test1 t1(1);
    Test1 t2(2);
    Test1 t3(2);
   Wang::Linklist<Test1> aa;
   aa.insert(t1);
   aa.insert(t2);
   aa.insert(t3);
   cout << aa.find(t2)<<endl;*/
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
   //////////////////////////////////
   ///////////////////////////////////
   //////////////单链表的遍历
   Wang::Linklist<int> List1;
   for(int i=0;i<5;i++)
   {
       List1.insert(0,i);
   }
    for(List1.move(0);!List1.end();List1.next())
   {
      cout<<List1.current()<<endl;
   }

    return 0;
}

*/
