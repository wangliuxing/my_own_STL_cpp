#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include "12-Object.h"
#include "35-Queue.h"
#include "22-Linklist.cpp"
#include "33-LinuxList.h"
using namespace std;

namespace Wang
{
template<typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_length;
public:
    StaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }
    int capacity()const
    {
        return N;
    }
    virtual void add(const T& e)
    {
        if(m_length<N)
        {
            m_space[m_rear] = e;
            m_rear = (m_rear+1)%N;
            m_length++;
        }
        else
        {
            //抛出异常
        }
    }
    virtual void remove()
    {
        if(m_length>0)
        {
            m_front = (m_front+1)%N;
            m_length--;
        }
        else
        {
            //抛出异常
        }
    }
    virtual T front() const
    {
        if(m_length>0)
        {
            return m_space[m_front];
        }
    }
    virtual void clear()
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }
    virtual int length() const
    {
        return m_length;
    }
};
/**
template<typename T>
class LinkQueue : public Object
{
protected:
    Linklist<int> m_list;
public:
    LinkQueue()
    {

    }
    virtual void add(const T& e)
    {
        m_list.insert(e);//O(n)
    }
    virtual void remove()
    {
        if(m_list.length()>0)
        {
            m_list.remove(0);
        }
        else
        {
            //抛出异常
        }
    }
    virtual T front() const
    {
        if(m_list.length()>0)
        {
            return m_list.get(0);
        }
    }
    virtual void clear()
    {
        m_list.clear();
    }
    virtual int length() const
    {
        return m_list.length();
    }
};
*/
template<typename T>
class LinkQueue : public Queue<T>
{
protected:
    struct Node : public Object
    {
        Node* pre;
        T value;
        Node* next;
    };
    struct : public Object
    {
        Node* pre;
        char a[sizeof(T)];
        Node* next;
    }m_header;
    int m_length;
public:
    LinkQueue()
    {
        m_length = 0;
        m_header.next = reinterpret_cast<Node*>(&m_header);
        m_header.pre = reinterpret_cast<Node*>(&m_header);
    }
    virtual void add(const T& e)
    {
        Node *node = new Node();
        if(node != NULL)
        {
            node->value = e;

            node->pre = m_header.pre;
            m_header.pre->next = node;
            node->next = reinterpret_cast<Node*>(&m_header);
            m_header.pre = node;

            m_length++;
        }
        else
        {
            //抛出异常
        }
    }
    virtual void remove()
    {
        if(m_length>0)
        {
            Node* toDel = m_header.next;
            m_header.next = toDel->next;
            toDel->next->pre = reinterpret_cast<Node*>(&m_header);
            m_length --;
            delete toDel;
            toDel = NULL;
        }
    }
    virtual T front() const
    {
        if(m_length>0)
        {
           return m_header.next->value;
        }
    }
    virtual void clear()
    {
        while(m_length>0)
        {
            remove();
        }
    }
    virtual int length() const
    {
        return m_length;
    }
    ~LinkQueue()
    {
        clear();
    }
};
}
#endif // _STACK_H
