#ifndef _SHAREDPOINT
#define _SHAREDPOINT

#include "27-Pointer.h"
#include <cstdlib>
using namespace std;
namespace Wang
{
    template<typename T>
    class Sharedpoint : public Pointer<T>
    {
protected:
    int *m_ref;
    void assign(const Sharedpoint<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if(this->m_ref)//如果这个地址不为空，申请成功了
        {
            (*this->m_ref)++;//再一次进行标识
            *(const_cast<Sharedpoint<T>&>(obj).m_ref) = *this->m_ref;
        }
    }
public:
    Sharedpoint(T *p = NULL) : m_ref(NULL)
    {
        if(p)
        {
            this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));
            //从堆空间申请一片内存，用于存储m_ref
            if(this->m_ref)//如果申请成功
            {
                *(this->m_ref) = 1;
                this->m_pointer = p;//用p对m_pointer进行初始化
            }
            else
            {
                //抛出异常
            }
        }
    }
    Sharedpoint(const Sharedpoint<T> &obj)
    {
        assign(obj);
        // 1：对this进行初始化 2：两个智能指针的m_ref++
    }
    Sharedpoint<T>& operator =(const Sharedpoint<T> &obj)
    {
        if(this != &obj)
        {
            clear();//当前的智能指针置空
            assign(obj);
        }
        return *this;
    }
    void clear()
    {
        T *toDel = this->m_pointer;
        int *ref = this->m_ref;//防止异常抛出
        this->m_pointer = NULL;
        this->m_ref = NULL;
        if(ref)//ref不为空，有地址
        {
            (*ref)--;
            if(*ref == 0)
            {
                free(ref);
                delete toDel;
            }
        }
    }
    ~Sharedpoint()
    {
        clear();
    }
    };
    template <typename T>
    bool operator == (const Sharedpoint<T>& Q,const Sharedpoint<T>& W)
    {
        return (Q.get()== W.get());
    }
    template <typename T>
    bool operator != (const Sharedpoint<T>& Q,const Sharedpoint<T>& W)
    {
        return !( Q == W );//使用==操作符
    }
}
#endif // _SHAREDPOINT
