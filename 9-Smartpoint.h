#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "Pointer.h"

using namespace std;
namespace Wang
{
    template<typename T>
    class Smartpoint : public Pointer<T>
    {
    public:
        Smartpoint(T *p = NULL) : Pointer<T>(p)
        {

        }
        Smartpoint(const Smartpoint<T>& obj)
        {
           this->m_pointer = obj.m_pointer;

           const_cast<Smartpoint<T>&>(obj).m_pointer = NULL;
        }
        Smartpoint<T>& operator = (const Smartpoint<T>& obj)
        {
            if(this != NULL)
            {
                T *p = this->m_pointer; //防止发生异常抛出

                delete this->m_pointer; //其实不删除也可以

                this->m_pointer = obj.m_pointer;

                const_cast<Smartpoint<T>&>(obj).m_pointer = NULL;

                delete p;
            }
            return *this;//支持连续的赋值
        }
        ~Smartpoint()
        {
            delete this->m_pointer;
        }
    };
}
/*
class test
{
public:
    test()
    {
        cout<<"test()"<<endl;
    }
    ~test()
    {
        cout<<"~test()"<<endl;
    }
};

int main()
{
    Wang::Smartpoint<test> p = new test();
    Wang::Smartpoint<test> sp;
    sp = p;//sp指向堆空间了，
    cout << sp.isNull()<<endl;
    cout << p.isNull()<<endl;
    return 0;
}
*/
