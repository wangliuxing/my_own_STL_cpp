#ifndef _LIST_H
#define _LIST_H

#include <iostream>
#include "12-Object.h"
using namespace std;

namespace Wang
{
template<typename T>
class List : public Object
{
protected:
    List(const List&);
    List &operator =(const List&);//不允许拷贝构造
public:
    List(){}
    virtual bool insert(const T &e)=0;//在线性表的尾部插入
    virtual bool insert(int i, const T &e)=0;//讲元素插入线性表
    virtual bool remove(int i)=0;//把i处元素从线性表中删除
    virtual bool set(int i, const T &e)=0;//设置i处元素
    virtual bool get(int i, T &e)const =0;//获取i处元素的值
    virtual int length() const =0;//获取线性表的长度
    virtual int find(const T&e) const=0;
    virtual void clear()=0;//清空线性表
};
template<typename T>
class SeqList : public List<T>
{
protected:
    T *m_arry;   //顺序存储空间，在此并不用对这个指针赋值
    int m_length;//当前线性表的长度
public:
    bool insert(int i, const T &e)//时间复杂度：n+5=>n
    {
        bool ret = ((i>=0)&&(i<=m_length));
        ret = ret && ((m_length+1)<=capacity());
        if(ret)
        {
            for(int p = m_length-1; p>=i; p--)//p和i都表示位置//n
            {
                m_arry[p+1]=m_arry[p];
            }
            m_length++;
            m_arry[i]=e;
        }
    return ret;
    }
    bool remove(int i)
    {
        bool ret = ((i>=0)&&(i<=m_length));

        if(ret)
        {
            for(int p = i; p<=m_length-1; p++)//p和i都表示位置//时间复杂度：n-1
            {
                m_arry[p]=m_arry[p+1];
            }
            m_length--;
        }
        return ret;
    }
    bool set(int i, const T &e)//用别名是考虑到效率
    {
        bool ret = ((i>=0)&&(i<=m_length));
        if(ret)
        {
            m_arry[i]=e;
        }
        return ret;
    }
    bool get(int i, T &e)const //表示当前操作是否成功
    {
        bool ret = ((i>=0)&&(i<=m_length));
        if(ret)
        {
            e = m_arry[i];
        }
        return ret;//如果i不合法，无法返回e，所以设置返回值为bool
    }
    int length() const
    {
        return m_length;
    }
    void clear()
    {
        m_length = 0;
    }
    T& operator[](int i)
    {
        if ((0<=i)&&(i<m_length))
        {
            return m_arry[i];
        }
        else
        {
            //抛出异常
        }
    }
    T operator[](int i) const//区分const和非const版本
    {
        if ((0<=i)&&(i<m_length))
        {
            return m_arry[i];
        }
        else
        {
            //抛出异常
        }
        //return (const_cast<SeqList<T>&>(*this))[i];
        //实现代码复用，调用非const版本
    }
    virtual bool push_back(const T &e)
    {
        return insert(m_length,e);
    }
    virtual int find(const T &e)const   //O(n)
    {
        for(int i=0;i<m_length;i++)
        {
            if(m_arry[i]==e)
            {
                return i;
            }
            else{return -1;}
        }
    }
    virtual int capacity() const =0;//获取存储空间的最大容量
};
/////////////////////////////////////////////////////////////////
///////////////////通过StaticList和DynamicList实现capacity()/////////////////////
/////////////////////////////////////////////////////////////////
template<typename T, int N>
class StaticList : public SeqList<T>
{
protected:
    T m_space[N];//顺序存储空间的最大容量
public:
    StaticList()
    {
        this->m_arry = m_space;
        this->m_length = 0;
    }
    int capacity() const
    {
        return N;
    }
};

template<typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;//顺序存储空间的大小
public:
    DynamicList(int capacity)//申请空间
    {
        this->m_arry = new T[capacity];
        if(this->m_arry!=NULL)
        {
            this->m_length = 0;
            this->m_capacity = capacity ;
        }
        else
        {
            //抛出异常
        }
    }
    int capacity() const
    {
        return m_capacity;
    }
    void resize(int capacity)//重置存储空间的大小,设置新的存储空间的大小capacity
    {
        if(capacity != m_capacity)
        {
            T* array = new T[capacity];
            if ( array!=NULL )
            {
                int length = (this->m_length < capacity)? this->m_length : capacity;
                for(int i=0;i<length;i++)
                {
                    array[i]=this->m_array[i];//保存各个空间的元素//可能发生异常
                }
                T *temp = this->m_arry;
                this->m_arry = array;
                this->m_length = length;
                this->m_capacity = capacity;
                delete[] temp;
            }
        }
        else
            {
                //抛出一个异常
               // Wang::Exception("NO memory to resize...",__FILE__,__LINE__);
            }
    }
    ~DynamicList()//归还空间
    {
        delete []this->m_arry;
    }

};

}
#endif // _LIST_H
/*
int main()
{
    Wang::StaticList<int, 5> l ;
    for(int i=0; i<l.capacity(); i++)
    {
        l.insert(0,i);//先插入数据再进行访问
    }
    for(int i=0; i<l.length(); i++)
    {
        cout << l[i] << endl;//重载操作符
    }

    Wang::DynamicList<int> p(5) ;
    for(int i=0; i<p.capacity(); i++)
    {
        p.insert(0,i);
    }
    for(int i=0; i<p.length(); i++)
    {
        cout << p[i] << endl;//重载操作符
    }

    return 0;
}
*/
