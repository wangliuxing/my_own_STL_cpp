#ifndef DUALCIRCLE_H
#define DUALCIRCLE_H

#include <iostream>
#include "30-DualLinkList.h"
#include "33-LinuxList.h"
using namespace std;

namespace Wang
{
template<typename T>
class DualCircleLinklist : public DualLinklist<T>
{
protected:
    struct Node : public Object
    {
       list_head pointer;
       T value;//list_head包含*next和*prev
    };
    list_head m_header;
    list_head* m_current;
    list_head* position(int i) const
    {
        list_head* ret = const_cast<list_head*>(&m_header);
        for(int p=0;p<i;p++)
        {
            ret = ret->next;
        }
        return ret;
    }
    int mod(int i) const
    {
        return (this->m_length == 0)? 0 : (i%this->m_length);
    }
public:
    DualCircleLinklist()
    {
        this->m_length = 0;
        this->m_step = 1;
        m_current = NULL;
        INIT_LIST_HEAD(&m_header);//对头结点进行初始化
    }
    bool insert(const T &e)
    {
        return insert(this->m_length,e);
    }
    bool insert(int i, const T &e)
    {
        bool ret = true;
        if(ret)
        {
            Node *node = new Node();
            i = i%(this->m_length + 1);
            if(node!=NULL)
            {
                node->value = e;
                list_add_tail(&node->pointer,position(i)->next);
                this->m_length++;
            }
            else
            {
                //抛出一个异常THROW_EXCPTION(EXCPTION,"No memory to insert element...")
            }
        }
        return ret;
    }
    bool remove(int i)
    {
        i=mod(i);
        bool ret =((0<=i)&&(i< this->m_length));
            if(ret)
            {
                list_head* toDel = position(i)->next;
                if(this->m_current == toDel)
                {
                    this->m_current = toDel->next;
                }
                list_del(toDel);
                this->m_length--;

                delete list_entry(toDel, Node ,pointer);
                //相当于container_of
                //通过head的地址减去偏移量获取toDel的地址
            }
            return ret;
    }

    bool set(int i, const T &e)//设置i处元素
    {
        bool ret = true;
        i = mod(i);
        ret = ((0<=i)&&(i< this->m_length));
        if(ret)
        {
            list_entry(position(i)->next, Node, pointer)->value = e;
        }
           return ret;

    }
    virtual T get(int i) const
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
        return ret;
    }
   virtual bool get(int i, T &e)const //获取i处元素的值
    {
        bool ret = true;

        i = mod(i);

        ret = ((0<=i)&&(i< this->m_length));


        if(ret)
        {
            e = list_entry(position(i)->next,Node,pointer)->value;
        }
           return ret;
    }
    int find(const T &e)const   //O(n)
    {
        int ret = -1;
        int i = 0;
        list_head* slider = NULL;
        list_for_each(slider , &m_header)
        {
            if(list_entry(slider, Node, pointer)->value == e)
            {
                ret = i;
                break;
            }
            i++;
        }
        return ret;
    }
    int length() const //获取线性表的长度
    {
        return this->m_length;
    }
    void clear()//清空线性表//头结点没有值，所以不删除
    {
        while(this->m_length>0)
        {
            remove(0);
        }
    }
   virtual bool move(int i,int step=1)//移动到目标位置
    {
        i = mod(i);
        bool ret = (0<=i)&&(i < this->m_length)&&(step>0);
        if(ret)
        {
            m_current = position(i)->next;//移动到i位置，为当前位置的下一个位置
            this->m_step = step;
        }
        return ret;
    }
   bool end()
    {
        return (m_current == NULL)||(this->m_length == 0);
    }
   virtual T current()
    {
        if(m_current!=NULL)
        {
            return list_entry(m_current, Node ,pointer)->value;
        }
        else
        {
            //抛出异常THROW_EXCEPTION(EXCEPTION)
        }
    }
   virtual bool next()
    {
        int i = 0;
        while((i<this->m_step)&&(m_current != NULL))
        {
            if(m_current != &m_header)
            {
                m_current = m_current->next;
                i++;
            }
            else
            {
                m_current = m_current->next;//跳过头结点
            }//在自己创建的链表中，头结点不参与遍历（独立的）
        }
        if(m_current == &m_header)
        {
            m_current = m_current->next;
        }
        return (i==this->m_step);
    }
    virtual bool pre()
    {
        int i = 0;
        while((i<this->m_step)&&(m_current != NULL))
        {
            if(m_current != &m_header)
            {
                m_current = m_current->prev;
                i++;
            }
            else
            {
                m_current = m_current->prev;//跳过头结点
            }
        }
        if(m_current == &m_header)
        {
            m_current = m_current->prev;
        }
        return (i== this->m_step);
    }
    ~DualCircleLinklist()
    {
        clear();
    }
};
}
#endif // DUALCIRCLE_H
