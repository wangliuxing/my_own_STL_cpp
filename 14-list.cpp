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
    List &operator =(const List&);//��������������
public:
    List(){}
    virtual bool insert(const T &e)=0;//�����Ա���β������
    virtual bool insert(int i, const T &e)=0;//��Ԫ�ز������Ա�
    virtual bool remove(int i)=0;//��i��Ԫ�ش����Ա���ɾ��
    virtual bool set(int i, const T &e)=0;//����i��Ԫ��
    virtual bool get(int i, T &e)const =0;//��ȡi��Ԫ�ص�ֵ
    virtual int length() const =0;//��ȡ���Ա��ĳ���
    virtual int find(const T&e) const=0;
    virtual void clear()=0;//������Ա�
};
template<typename T>
class SeqList : public List<T>
{
protected:
    T *m_arry;   //˳��洢�ռ䣬�ڴ˲����ö����ָ�븳ֵ
    int m_length;//��ǰ���Ա��ĳ���
public:
    bool insert(int i, const T &e)//ʱ�临�Ӷȣ�n+5=>n
    {
        bool ret = ((i>=0)&&(i<=m_length));
        ret = ret && ((m_length+1)<=capacity());
        if(ret)
        {
            for(int p = m_length-1; p>=i; p--)//p��i����ʾλ��//n
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
            for(int p = i; p<=m_length-1; p++)//p��i����ʾλ��//ʱ�临�Ӷȣ�n-1
            {
                m_arry[p]=m_arry[p+1];
            }
            m_length--;
        }
        return ret;
    }
    bool set(int i, const T &e)//�ñ����ǿ��ǵ�Ч��
    {
        bool ret = ((i>=0)&&(i<=m_length));
        if(ret)
        {
            m_arry[i]=e;
        }
        return ret;
    }
    bool get(int i, T &e)const //��ʾ��ǰ�����Ƿ�ɹ�
    {
        bool ret = ((i>=0)&&(i<=m_length));
        if(ret)
        {
            e = m_arry[i];
        }
        return ret;//���i���Ϸ����޷�����e���������÷���ֵΪbool
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
            //�׳��쳣
        }
    }
    T operator[](int i) const//����const�ͷ�const�汾
    {
        if ((0<=i)&&(i<m_length))
        {
            return m_arry[i];
        }
        else
        {
            //�׳��쳣
        }
        //return (const_cast<SeqList<T>&>(*this))[i];
        //ʵ�ִ��븴�ã����÷�const�汾
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
    virtual int capacity() const =0;//��ȡ�洢�ռ���������
};
/////////////////////////////////////////////////////////////////
///////////////////ͨ��StaticList��DynamicListʵ��capacity()/////////////////////
/////////////////////////////////////////////////////////////////
template<typename T, int N>
class StaticList : public SeqList<T>
{
protected:
    T m_space[N];//˳��洢�ռ���������
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
    int m_capacity;//˳��洢�ռ�Ĵ�С
public:
    DynamicList(int capacity)//����ռ�
    {
        this->m_arry = new T[capacity];
        if(this->m_arry!=NULL)
        {
            this->m_length = 0;
            this->m_capacity = capacity ;
        }
        else
        {
            //�׳��쳣
        }
    }
    int capacity() const
    {
        return m_capacity;
    }
    void resize(int capacity)//���ô洢�ռ�Ĵ�С,�����µĴ洢�ռ�Ĵ�Сcapacity
    {
        if(capacity != m_capacity)
        {
            T* array = new T[capacity];
            if ( array!=NULL )
            {
                int length = (this->m_length < capacity)? this->m_length : capacity;
                for(int i=0;i<length;i++)
                {
                    array[i]=this->m_array[i];//��������ռ��Ԫ��//���ܷ����쳣
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
                //�׳�һ���쳣
               // Wang::Exception("NO memory to resize...",__FILE__,__LINE__);
            }
    }
    ~DynamicList()//�黹�ռ�
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
        l.insert(0,i);//�Ȳ��������ٽ��з���
    }
    for(int i=0; i<l.length(); i++)
    {
        cout << l[i] << endl;//���ز�����
    }

    Wang::DynamicList<int> p(5) ;
    for(int i=0; i<p.capacity(); i++)
    {
        p.insert(0,i);
    }
    for(int i=0; i<p.length(); i++)
    {
        cout << p[i] << endl;//���ز�����
    }

    return 0;
}
*/