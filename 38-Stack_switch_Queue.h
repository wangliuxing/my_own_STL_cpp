#ifndef _STATIC_SWITCH_STACK_QUEUE_H
#define _STATIC_SWITCH_STACK_QUEUE_H

#include <iostream>
#include "12-Object.h"
#include "35-Static_Link_Queue.h"
#include "34-Static_Link_Stack.h"
using namespace std;

namespace Wang
{
template<typename T>
class StackToQueue: public Queue<T>
{
protected:
    mutable LinkStack<T> m_stack_in;//进队列，进入m_stack_in栈
    mutable LinkStack<T> m_stack_out;//出队列，出m_stack_out栈
    void move() const//需要出队列时但出队列的栈是空的
    {
        if(m_stack_out.size()==0)
        {
            while(m_stack_in.size() > 0)//O(n)
            {
                m_stack_out.push(m_stack_in.top());
                m_stack_in.pop();
            }
        }
    }
public:
    void add(const T& e)
    {
        m_stack_in.push(e);
    }
    void remove()
    {
        move();//O(n)

        if(m_stack_out.size()>0)//栈不为空
        {
            m_stack_out.pop();
        }
        else
        {
            //抛出一个异常
        }
    }
    T front() const
    {
        move();//O(n)
        if(m_stack_out.size()>0)
        {
            return m_stack_out.top();
        }
    }
    void clear()
    {
        m_stack_in.clear();
        m_stack_out.clear();
    }
    int length()
    {
        return m_stack_in.size() + m_stack_out.size();
    }
};
template<typename T>
class Queue_to_Stack : public Stack<T>
{
protected:
    LinkQueue<T> m_queue_1;
    LinkQueue<T> m_queue_2;
    LinkQueue<T> *m_pIn;
    LinkQueue<T> *m_pOut;//用于指向队列的指针
    void move() const//O(N)
    {
        int n = m_pIn->length()-1;//转移n-1个元素
        for(int i =0; i<n;i++)
        {
            m_pOut->add(m_pIn->front());//进行转移
            m_pIn->remove();//把入队列的元素进行出列
        }
    }
    void swap()//队列交换函数
    {
        LinkQueue<T>* temp= NULL;
        temp = m_pIn;
        m_pIn = m_pOut;
        m_pOut = temp;
    }
public:
    Queue_to_Stack()
    {
        m_pIn = &m_queue_1;
        m_pOut = &m_queue_2;
    }
    void push(const T& e)
    {
        m_pIn->add(e);
    }
    void pop()
    {
        if(m_pIn->length()>0)
        {
            move();
            m_pIn->remove();//出栈
            swap();//交换进队列和出队列
        }
        else
        {
            //抛出异常
        }
    }
    T top() const//O(n)
    {
        if(m_pIn->length()>0)
        {
            move();
            return m_pIn->front();
        }
/*  else
        {
            //抛出异常
        }
*/
    }
    void clear()//O(n)
    {
        m_queue_1.clear();
        m_queue_2.clear();
    }
    int size() const
    {
        return m_queue_1.length() + m_queue_2.length();
    }
};
}
#endif // _QUEUE_H
