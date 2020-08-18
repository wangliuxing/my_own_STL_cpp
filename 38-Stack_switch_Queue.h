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
    mutable LinkStack<T> m_stack_in;//�����У�����m_stack_inջ
    mutable LinkStack<T> m_stack_out;//�����У���m_stack_outջ
    void move() const//��Ҫ������ʱ�������е�ջ�ǿյ�
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

        if(m_stack_out.size()>0)//ջ��Ϊ��
        {
            m_stack_out.pop();
        }
        else
        {
            //�׳�һ���쳣
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
    LinkQueue<T> *m_pOut;//����ָ����е�ָ��
    void move() const//O(N)
    {
        int n = m_pIn->length()-1;//ת��n-1��Ԫ��
        for(int i =0; i<n;i++)
        {
            m_pOut->add(m_pIn->front());//����ת��
            m_pIn->remove();//������е�Ԫ�ؽ��г���
        }
    }
    void swap()//���н�������
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
            m_pIn->remove();//��ջ
            swap();//���������кͳ�����
        }
        else
        {
            //�׳��쳣
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
            //�׳��쳣
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