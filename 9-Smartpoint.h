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
                T *p = this->m_pointer; //��ֹ�����쳣�׳�

                delete this->m_pointer; //��ʵ��ɾ��Ҳ����

                this->m_pointer = obj.m_pointer;

                const_cast<Smartpoint<T>&>(obj).m_pointer = NULL;

                delete p;
            }
            return *this;//֧�������ĸ�ֵ
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
    sp = p;//spָ��ѿռ��ˣ�
    cout << sp.isNull()<<endl;
    cout << p.isNull()<<endl;
    return 0;
}
*/