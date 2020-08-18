#ifndef _STATIC_LINK_STACK_H
#define _STATIC_LINK_STACK_H
#include <iostream>
#include "12-Object.h"
#include "22-Linklist.cpp"
using namespace std;

namespace Wang
{
template<typename T>
class Stack : public Object
{
public:
    virtual void push(const T& e) = 0 ;
    virtual void pop() = 0 ;
    virtual T top() const = 0 ;
    virtual void clear() = 0 ;
    virtual int size() const = 0 ;
};
template< typename T, int N >
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_size;
    int m_top;
public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }
    int capacity() const
    {
        return N;
    }
    void push(const T& e)
    {
        if(m_size < N)
        {
            m_space[m_top + 1]=e;//e可能是类类型，异常安全
            m_top++;
            m_size++;
        }
        else
        {
            //抛出异常
        }
    }
    void pop()
    {
        if(m_size > 0)
        {
            m_top--;
            m_size--;
        }
        else
        {
            //抛出异常
        }
    }
    T top() const
    {
        if(m_size > 0)
        {
            return m_space[m_top];
        }
        else
        {
            //抛出异常
        }
    }
    void clear()
    {
        m_top = -1;
        m_size = 0;
    }
    int size() const
    {
        return m_size;
    }
};
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
template<typename T>
class LinkStack : public Stack<T>
{
protected:
    Linklist<T> m_list;
public:
    void push(const T& e)
    {
        m_list.insert(0,e);
    }
    void pop()
    {
        if(m_list.length()>0)
            m_list.remove(0);
        else
          {
                //抛出异常
          }
    }
    T top() const
    {
        if(m_list.length()>0)
            return m_list.get(0);
        else
            {
                //抛出异常
            }
    }
    void clear()
    {
       m_list.clear();
    }
    int size() const
    {
        return m_list.length();
    }
};
}
#endif // _STACK_H
/**
#include <iostream>
#include "34-Static_Link_Stack.h"
using namespace std;
using namespace Wang;

bool is_left(char c)
{
    return (c=='(')||(c=='{')||(c=='[')||(c=='<');
}
bool is_right(char c)
{
    return (c==')')||(c=='}')||(c==']')||(c=='>');
}
bool is_quit(char c)
{
    return (c=='\'')||(c=='\"');
}
bool is_match(char l, char r)
{
    return ((l=='(')&&(r==')'))||
    ((l=='{')&&(r=='}'))||
    ((l=='[')&&(r==']'))||
    ((l=='<')&&(r=='>'))||
    ((l=='\'')&&(r=='\''))||
    ((l=='\"')&&(r=='\"'));
}
bool scan(const char *code)
{
    LinkStack<char> stack1;
    int i =0 ;
    bool ret = true;

    code = ((code==NULL)? "" : code);
    while(ret && (code[i]!='\0'))
    {
        if(is_left(code[i]))
        {
            stack1.push(code[i]);
        }
        else if(is_right(code[i]))
        {
            if((stack1.size()>0)&&(is_match(stack1.top(),code[i])))
            {
                stack1.pop();
            }
            else
            {
                ret = false;
            }
        }
        else if(is_quit(code[i]))
        {
            if((stack1.size() == 0) ||(!is_match(stack1.top(),code[i])))
            {
                stack1.push(code[i]);
            }
            else if(is_match(stack1.top(),code[i]))
            {
                stack1.pop();
            }
        }
        i++;
    }
    return ret&&(stack1.size()==0);
}
int main()
{
    cout<<scan("<abcd")<<endl;
    return 0;
}
*/
