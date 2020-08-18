#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include "12-Object.h"
using namespace std;

namespace Wang
{
template<typename T>
class Array : public Object
{
protected:
    T* m_array;
public:
    virtual bool set(int i,const T& e)
    {
        bool ret = ((0<=i)&&(i<=length()));
        if(ret)
        {
            m_array[i]=e;
        }
        return ret;
    }
    virtual bool get(int i,T& e)const
    {
        bool ret = ((0<=i)&&(i<=length()));
        if(ret)
        {
            e = m_array[i];
        }
        return ret;
    }
    T &operator[](int i)
    {
        if ((0<=i)&&(i<=length()))
        {
            return m_array[i];
        }
        else
        {
        //抛出异常 THROW_EXCEPTION(Index,"Parament");
        }
    }
    T operator[](int i)const
    {
        return (const_cast<Array<T>&>(*this)[i]);
       // return (const_cast<Array<T>&>(m_array)[i]);
    }
    T* array()const
    {
        return m_array;
    }
     virtual int length()const =0;
};

template<typename T, int N>
class StaticArray : public Array<T>
{
protected:
    T m_space[N];
public:
    StaticArray()
    {
        this->m_array = m_space;//把子类创建的对象和父类创建的对象进行挂接
    }
    StaticArray(const StaticArray<T,N>&obj)//0(n)
    {
        this->m_array = m_space;
        for(int i;i<N;i++)
        {
            m_space[i]=obj.m_space[i];
        }
    }

    StaticArray<T,N>& operator = (const StaticArray<T,N>&obj)
    {
        if (this != &obj)
        {
            for(int i=0;i<N;i++)
            {
                m_space[i]=obj.m_space[i];
            }

        }
        return *this;
    }

    int length()const
    {
        return N;
    }

};
template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;
    T *copy(T* array, int len,int newLen)//申请新的堆空间，并进行拷贝
    {                                       //O(min(len , newLen)) ===>O(n)
        T *ret = new T[newLen];
        if (ret)
        {
            int size = (len < newLen)?len:newLen;
            for (int i=0; i<size;i++)
            {
                ret[i] = array[i];
            }
        }
        return ret;
    }
    void update(T* array, int length)//设置当前数组的值  // o(1)
    {
        if(array != NULL)
        {
            T *temp = this->m_array;
            this->m_array = array;
            this->m_length = length;
            delete[] temp;
        }
        else
        {
            //抛出异常
        }
    }
    void init(T *array, int length)// o(1)
    {
        if(array!= NULL)
        {
            this->m_array = array;
            this->m_length = length ;
        }
        else
        {
            //抛出异常
        }
    }
public:
    DynamicArray()
    {
        this->m_array = new T();
        if (this->m_array!=NULL)
        {
            this->m_length = 0;
        }
        else
        {
            //抛出一个异常 THROW_EXCEPTION(EXCEPTION, "No memory to create array..."
        }
    }
    DynamicArray(int length)   // o(1)
    {
        //init (new T[length], length);
        this->m_array = new T[length];
        if (this->m_array!=NULL)
        {
            this->m_length = length;
        }
        else
        {
            //抛出一个异常 THROW_EXCEPTION(EXCEPTION, "No memory to create array..."
        }
    }
    DynamicArray(const DynamicArray<T>& obj)
    {
        ////////////////////////////////////////////
/*
T *array = copy(obj.m_array,obj.m_length,obj.m_length);
init(array, obj.m_length);

*/
        this->m_array = new T[obj.length];
        if (this->m_array!=NULL)
        {
            this->m_length = obj.length;
            for(int i=0;i<obj.m_length;i++)
            {
                this->m_array[i] = obj.m_array[i];
            }
        }
        else
        {
        //抛出一个异常 THROW_EXCEPTION(EXCEPTION, "No memory to create array..."
        }
    }
    DynamicArray<T>& operator = (const DynamicArray<T>& obj)
    {
        if (this != &obj)
        {
/*
        T *array = copy(obj.m_array,obj.length,obj.m_length);
        update(array,obj.m_length);
        //或者 update(copy(obj.m_array,obj.length,obj.m_length),obj.m_length);
*/
            T *array = new T[obj.m_length];
            if (array != NULL)
            {
                for(int i=0;i<obj.m_length;i++)
                {
                    array[i] = obj.m_array[i];
                }
                T *temp = this->m_array;
                this->m_array = array;
                this->m_length = obj.m_length;
                delete[] temp;
            }
        }
        else
        {
        //抛出一个异常 THROW_EXCEPTION(EXCEPTION, "No memory to create array..."
        }
         return *this;
    }
    int length()const
    {
        return m_length;
    }
    void resize(int length)//重置数组大小
    {
        if(length != m_length)
        {
/*
        T *array = copy(this->m_array,m_length,length);
        update(array,length);
        //或者 update(copy(this->m_array,m_length,length),obj.m_length);
*/
            T *array = new T[length];
            if(array != NULL)//判断申请是否成功
            {
                int size = (length<m_length)?length:m_length;
                for (int i=0; i<size; i++)
                {
                    array[i] = this->m_array[i];
                }
                T *temp= this -> m_array;//考虑安全的目的
                this -> m_array = array;
                this -> m_length = length ;
                delete []temp;

            }
            else
            {
                //抛出一个异常
            }
        }
    }
    ~DynamicArray()
    {
        delete []this->m_array;
    }

};
}
/**
int main()
{
    Wang::StaticArray<int,5>s1;
    Wang::StaticArray<int,5>s2;
    for (int i=0; i<s1.length();i++)
    {
        s1[i]=i*i;
    }
    for (int i=0; i<s1.length();i++)
    {
        cout<<s1[i]<<endl;
    }
    s2 = s1;
    for (int i=0; i<s2.length();i++)
    {
        cout<<s2[i]<<endl;
    }
    cout<<endl;
    Wang::DynamicArray<int>s3(5);
    for (int i=0; i<s3.length();i++)
    {
        s1[i]=i*i;
    }
    for (int i=0; i<s3.length();i++)
    {
        cout<<s1[i]<<endl;
    }
    Wang::DynamicArray<int>s4(10);
    s4 = s3;
    for (int i=0; i<s4.length();i++)
    {
        cout<<s4[i]<<endl;
    }
    return 0;
}
*/
#endif // ARRAY_H
